#pragma once
#include <queue>
#include <string>
#include "HttpClient.h"
#include "FilenameQueue.h"
#include "AudioQueue.h"

const std::string HTTP_INI_FILE = "..\\config\\http_config.ini";

int RECORDING_TIME;
int SAMPLE_RATE;
int INPUT_CHANNELS_COUNT;
int OUTPUT_CHANNELS_COUNT;
const int FRAME_PER_BUFFER = 1024;
const float SLOW_RATIO = 1.25;


std::string previous_filename = "";

FilenameQueue filename_queue = FilenameQueue();
FilenameQueue delete_queue = FilenameQueue();
AudioQueue audio_queue = AudioQueue(SAMPLE_RATE * 100);

std::atomic<bool> stop_signal(false);

void signal_handler(int signal);

void clean_old_files(const std::vector<std::string>& filename_list, HttpClient& client);

void recorder_thread(HttpClient& client, FilenameQueue& filename_queue);
void downloader_thread(HttpClient& client, FilenameQueue& filename_queue, AudioQueue& audioQueue, FilenameQueue& delete_queue);
void player_thread(AudioQueue& audioQueue);