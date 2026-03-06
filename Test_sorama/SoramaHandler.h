#pragma once
#include <queue>
#include <string>
#include "HttpClient.h"
#include "FilenameQueue.h"
#include "AudioQueue.h"

const std::string HTTP_INI_FILE = "C:\\Users\\huykh\\source\\repos\\Test_sorama\\Test_sorama\\http_config.ini";

const int SAMPLE_RATE = 46875;
const int INPUT_CHANNELS_COUNT = 1;
const int OUTPUT_CHANNELS_COUNT = 1;
const int FRAME_PER_BUFFER = 1024;
const float SLOW_RATIO = 1.25;

FilenameQueue filename_queue = FilenameQueue();
AudioQueue audio_queue = AudioQueue(SAMPLE_RATE * 100);

std::atomic<bool> stop_signal(false);

void signal_handler(int signal);

void clean_old_files(const std::vector<std::string>& filename_list, HttpClient& client);

void recorder_thread(HttpClient& client, FilenameQueue& filename_queue);
void downloader_thread(HttpClient& client, FilenameQueue& filename_queue, AudioQueue& audioQueue);
void player_thread(AudioQueue& audioQueue);