#include <iostream>
#include <curl/curl.h>
#include <sndfile.h>
#include <portaudio.h>
#include "SoramaHandler.h"
#include "HttpClient.h"
#include "Parser.h"
#include <thread>
#include <chrono>
#include "FilenameQueue.h"
#include "AudioQueue.h"
#include <csignal>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        stop_signal.store(true);
        std::cout << "\n Stopping...\n";
    }
}

void clean_old_files(const std::vector<std::string>& filename_list, HttpClient& client)
{
    std::cout << "Cleaning old files" << std::endl;

    for (size_t i = 0; i < filename_list.size(); i++) {
        client.delete_audio_file(filename_list[i]);
    }
}

std::vector<float> slowDownAudio(
    const std::vector<float>& in)
{
    size_t newSize = static_cast<size_t>(in.size() * SLOW_RATIO);
    std::vector<float> out(newSize);

    for (size_t i = 0; i < newSize; i++)
    {
        float index = i / SLOW_RATIO;

        size_t i0 = static_cast<size_t>(index);
        size_t i1;

        if (i0 + 1 < in.size())
            i1 = i0 + 1;
        else
            i1 = in.size() - 1;

        float frac = index - i0;

        out[i] = (1 - frac) * in[i0] + frac * in[i1];
    }

    return out;
}

void player_thread(AudioQueue& audioQueue) {
    Pa_Initialize();
    PaStream* stream;

    Pa_OpenDefaultStream(
        &stream,
        INPUT_CHANNELS_COUNT,
        OUTPUT_CHANNELS_COUNT,
        paFloat32,
        SAMPLE_RATE,
        FRAME_PER_BUFFER,
        nullptr,
        nullptr
    );

    Pa_StartStream(stream);

    std::vector<float> buffer(FRAME_PER_BUFFER * INPUT_CHANNELS_COUNT);

    while (!stop_signal.load()) {
        size_t n = audioQueue.pop(buffer.data(), FRAME_PER_BUFFER);
        if (n == 0) { // no data from audio queue
            std::fill(buffer.begin(), buffer.end(), 0.0f);
        }
        //else if (n < FRAME_PER_BUFFER) { // less data in audio queue than frame_per_buffer
        //    std::fill(buffer.begin() + n, buffer.end(), 0.0f);
        //} 
        //Pa_WriteStream(stream, slower_audio.data(), FRAME_PER_BUFFER);
        //continue as normal
        Pa_WriteStream(stream, buffer.data(), FRAME_PER_BUFFER);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}


void downloader_thread(HttpClient& client, FilenameQueue& filename_queue, AudioQueue& audio_queue)
{
    while (!stop_signal.load())
    {
        std::string recorded_filename = filename_queue.pop();
        if (!recorded_filename.empty()) {
            std::vector<char> audio_binary = client.get_audio_file(recorded_filename);

            while (audio_binary.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                audio_binary = client.get_audio_file(recorded_filename);
            }

            std::vector<float> samples = parse_wav_to_float(audio_binary);
            if (samples.empty()) continue;
            std::vector<float> slowed_sample = slowDownAudio(samples);


            size_t pushed = 0;
            while (pushed < samples.size()) {
                size_t remaining = samples.size() - pushed;
                size_t chunk = (FRAME_PER_BUFFER < remaining) ? FRAME_PER_BUFFER : remaining;

                audio_queue.push(samples.data() + pushed, chunk);
                pushed += chunk;
            }
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}


void recorder_thread(HttpClient& client, FilenameQueue& filename_queue)
{
    while (!stop_signal.load())
    {
        std::string recorded_filename = client.post_record_command();
        if (!recorded_filename.empty()) {
            filename_queue.push(recorded_filename);
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void cleaner_thread()
{

}


int main()
{   
    std::signal(SIGINT, signal_handler);

    std::cout << "Initializing Sorama" << std::endl;

    std::string sorama_IP = parse_ini_value(HTTP_INI_FILE, "Sorama", "IP");
    std::string sorama_username = parse_ini_value(HTTP_INI_FILE, "Sorama", "username");
    std::string sorama_pwd = parse_ini_value(HTTP_INI_FILE, "Sorama", "password");

    HttpClient http_client = HttpClient(sorama_IP, sorama_username, sorama_pwd);
    std::vector<std::string> filename_list = http_client.get_file_info();

    //clean_old_files(filename_list, http_client);

    // Start threads
    std::thread recorder(recorder_thread,
        std::ref(http_client),
        std::ref(filename_queue));

    std::thread player(player_thread,
        std::ref(audio_queue));
    
    
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::thread downloader(downloader_thread,
        std::ref(http_client),
        std::ref(filename_queue),
        std::ref(audio_queue));

    player.join();
    recorder.join();
    downloader.join();
}
