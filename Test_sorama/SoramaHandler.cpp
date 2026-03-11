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
#include <rubberband/RubberBandStretcher.h>

void signal_handler(int signal) {
    if (signal == SIGINT) {
        stop_signal.store(true);
        std::cout << "\n Stopping...\n";
    }
}

void clean_old_files(const std::vector<std::string>& filename_list, HttpClient& client)
{
    std::cout << "Cleaning old files" << std::endl;
    for (size_t i = 0; i < filename_list.size(); i++) 
    {
        client.delete_audio_file(filename_list[i]);
    }
}

std::vector<float> slowDownAudio(const std::vector<float>& in)
{
    if (in.empty()) return {};

    std::vector<float> sanitized = in;
    for (auto& s : sanitized) {
        if (std::isnan(s) || std::isinf(s)) s = 0.0f;
    }

    size_t frames = in.size() / OUTPUT_CHANNELS_COUNT;

    RubberBand::RubberBandStretcher stretcher(
        SAMPLE_RATE,
        OUTPUT_CHANNELS_COUNT,
        RubberBand::RubberBandStretcher::OptionProcessRealTime
    );

    stretcher.setTimeRatio(SLOW_RATIO);

    const float* inPtr[1] = { in.data() };

    stretcher.process(inPtr, frames, true);

    std::vector<float> output;
    output.reserve(in.size() * SLOW_RATIO);

    std::vector<float> outputBuffer(FRAME_PER_BUFFER * OUTPUT_CHANNELS_COUNT);
    float* outPtr[1] = { outputBuffer.data() };

    while (stretcher.available() > 0)
    {
        size_t availableFrames = stretcher.available();
        size_t framesToGet;

        if (availableFrames > FRAME_PER_BUFFER)
        {
            framesToGet = FRAME_PER_BUFFER;
        }
        else
        {
            framesToGet = availableFrames;
        }

        stretcher.retrieve(outPtr, framesToGet);

        size_t samples = framesToGet * OUTPUT_CHANNELS_COUNT;

        output.insert(
            output.end(),
            outputBuffer.begin(),
            outputBuffer.begin() + samples
        );
    }

    return output;
}

void player_thread(AudioQueue& audioQueue) {
    std::cout << "Player thread starts" << std::endl;
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

    PaDeviceIndex defaultDevice = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* info = Pa_GetDeviceInfo(defaultDevice);

    Pa_StartStream(stream);

    std::vector<float> buffer(FRAME_PER_BUFFER * OUTPUT_CHANNELS_COUNT);

    while (!stop_signal.load()) 
    {
        size_t n = audioQueue.pop(buffer.data(), FRAME_PER_BUFFER * OUTPUT_CHANNELS_COUNT);
        if (n == 0) 
        { // no data from audio queue
            std::fill(buffer.begin(), buffer.end(), 0.0f);
        }

        for (size_t i = 0; i < n * OUTPUT_CHANNELS_COUNT; i++)
        {
            buffer[i] = std::tanh(buffer[i] * AUDIO_GAIN);
        }
        
        //continue as normal
        Pa_WriteStream(stream, buffer.data(), FRAME_PER_BUFFER);
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}


void downloader_thread(HttpClient& client, FilenameQueue& filename_queue, AudioQueue& audio_queue, FilenameQueue& delete_queue)
{   
    std::cout << "Downloader thread starts" << std::endl;

    while (!stop_signal.load())
    {
        std::string recorded_filename = filename_queue.pop();
        std::cout << "Checking " << recorded_filename << std::endl;
        if (!recorded_filename.empty()) 
        {
            std::vector<char> audio_binary;

            int retry_count = 0;
            long http_code = client.get_audio_file(recorded_filename, audio_binary);

            while (http_code == 404 && retry_count < 12) {
                long http_code = client.get_audio_file(recorded_filename, audio_binary);
                retry_count += 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            if (http_code == 404)
            {   
                std::cout << "Not on sorama" << std::endl;
                continue;
            }

            std::cout << recorded_filename << " retrieved" << std::endl;
            //std::cout << "Filesize: " << audio_binary.size() << std::endl;

            retry_count = 0;
            while (audio_binary.size() < 100000 && retry_count < 12) 
            {
                http_code = client.get_audio_file(recorded_filename, audio_binary);
                //std::cout << "File name: " << recorded_filename << std::endl;
                //std::cout << "Audio size: " << audio_binary.size() << std::endl;
                retry_count += 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }

            std::vector<char> audio_data(audio_binary.begin() + 44, audio_binary.end());
            audio_binary.swap(audio_data);

            std::vector<float> samples = parse_wav_to_float(audio_binary);
            std::vector<float> slowedSamples;
            if (samples.empty() || samples.size() < 256) {
                //std::cout << "Skipping too-small file: " << recorded_filename << std::endl;
                slowedSamples = samples;
            }
            else
            {
                slowedSamples = slowDownAudio(samples);
            }


            size_t pushed = 0;
            while (pushed < slowedSamples.size()) 
            {
                size_t remaining = slowedSamples.size() - pushed;
                size_t chunk = (FRAME_PER_BUFFER < remaining) ? FRAME_PER_BUFFER : remaining;

                audio_queue.push(slowedSamples.data() + pushed, chunk);
                pushed += chunk;
            }
            
            if (!previous_filename.empty()) 
            {
                delete_queue.push(previous_filename);
            }
            previous_filename = recorded_filename;
            
        }
        else {
            continue;
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}


void recorder_thread(HttpClient& client, FilenameQueue& filename_queue)
{   
    std::cout << "Recorder thread starts" << std::endl;
    while (!stop_signal.load())
    {
        std::string recorded_filename;
        
        long http_code = client.post_record_command(recorded_filename);
        if (!recorded_filename.empty()) 
        {   
            //std::cout << "Pushing " << recorded_filename << std::endl;
            filename_queue.push(recorded_filename);
        }
        else 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::seconds(RECORDING_TIME));
    }
}

void cleaner_thread(HttpClient& client, FilenameQueue& delete_queue)
{
    std::cout << "Cleaner thread starts" << std::endl;
    while (!stop_signal.load())
    {
        std::string delete_filename = delete_queue.pop();
        client.delete_audio_file(delete_filename);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


int main()
{   
    std::signal(SIGINT, signal_handler);

    std::cout << "Initializing Sorama" << std::endl;

    try 
    {
        SORAMA_IP = parse_ini_value(HTTP_INI_FILE, "Sorama", "IP");
        SORAMA_USERNAME = parse_ini_value(HTTP_INI_FILE, "Sorama", "username");
        SORAMA_PWD = parse_ini_value(HTTP_INI_FILE, "Sorama", "password");

        RECORDING_TIME = std::stoi(parse_ini_value(HTTP_INI_FILE, "Sorama", "Recording_time"));
        OUTPUT_CHANNELS_COUNT = std::stoi(parse_ini_value(HTTP_INI_FILE, "Sorama", "Output_channel_count"));
        INPUT_CHANNELS_COUNT = std::stoi(parse_ini_value(HTTP_INI_FILE, "Sorama", "Input_channel_count"));
        SAMPLE_RATE = std::stoi(parse_ini_value(HTTP_INI_FILE, "Sorama", "Sample_rate"));
        AUDIO_GAIN = std::stof(parse_ini_value(HTTP_INI_FILE, "Sorama", "Audio_gain"));
        SLOW_RATIO = std::stof(parse_ini_value(HTTP_INI_FILE, "Sorama", "Slow_ratio"));
    } catch (...)
    {
        std::cout << "Failed to parse ini file" << std::endl;
        return -1;
    }

    AudioQueue audio_queue = AudioQueue(SAMPLE_RATE * 100);

    HttpClient http_client = HttpClient(SORAMA_IP, SORAMA_USERNAME, SORAMA_PWD, RECORDING_TIME);
    std::vector<std::string> filename_list = http_client.get_file_info();

    clean_old_files(filename_list, http_client);

    std::cout << "Finish Cleaning" << std::endl;

    // Start threads
    std::thread recorder(recorder_thread,
        std::ref(http_client),
        std::ref(filename_queue));

    std::thread player(player_thread,
        std::ref(audio_queue));
    
    
    std::this_thread::sleep_for(std::chrono::seconds(6));

    std::thread downloader(downloader_thread,
        std::ref(http_client),
        std::ref(filename_queue),
        std::ref(audio_queue),
        std::ref(delete_queue));

    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    /*
    std::thread cleaner(cleaner_thread,
        std::ref(http_client),
        std::ref(delete_queue));
    */

    // Join threads
    player.join();
    recorder.join();
    downloader.join();
    //cleaner.join();
}
