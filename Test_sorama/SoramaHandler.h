#pragma once
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

// Download config
int MAX_RETRIES;
int BUFFER_RECORDING_TIME;
int BUFFER_DOWNLOADING_TIME;

const int FRAME_PER_BUFFER = 4096;

std::string previous_filename = "";

FilenameQueue filename_queue = FilenameQueue();
FilenameQueue delete_queue = FilenameQueue();

// Program shutdown
std::atomic<bool> stop_signal(false);
void signal_handler(int signal);

// Clean old files
void clean_old_files(HttpClient& client);

// Slow down audio
std::vector<float> slowDownAudio(const std::vector<float>& in, RubberBand::RubberBandStretcher& stretcher);

// Threads
void recorder_thread(HttpClient& client, FilenameQueue& filename_queue);
void downloader_thread(HttpClient& client,
						FilenameQueue& filename_queue,
						AudioQueue& audioQueue,
						FilenameQueue& delete_queue,
						RubberBand::RubberBandStretcher& stretcher);
void player_thread(AudioQueue& audioQueue);