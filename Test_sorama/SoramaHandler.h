#pragma once
#include <queue>
#include <string>
#include "HttpClient.h"
#include "FilenameQueue.h"
#include "AudioQueue.h"

const std::string HTTP_INI_FILE = "..\\config\\http_config.ini";


// Sorama credentials
std::string SORAMA_IP;
std::string SORAMA_USERNAME;
std::string SORAMA_PWD;

// Audio player config
int RECORDING_TIME;
int SAMPLE_RATE;
int INPUT_CHANNELS_COUNT;
int OUTPUT_CHANNELS_COUNT;
float AUDIO_GAIN;
float SLOW_RATIO;

const int FRAME_PER_BUFFER = 1024;

std::string previous_filename = "";

FilenameQueue filename_queue = FilenameQueue();
FilenameQueue delete_queue = FilenameQueue();

// Program shutdown
std::atomic<bool> stop_signal(false);
void signal_handler(int signal);

// Clen old files
void clean_old_files(const std::vector<std::string>& filename_list, HttpClient& client);

// Threads
void recorder_thread(HttpClient& client, FilenameQueue& filename_queue);
void downloader_thread(HttpClient& client, FilenameQueue& filename_queue, AudioQueue& audioQueue, FilenameQueue& delete_queue);
void player_thread(AudioQueue& audioQueue);