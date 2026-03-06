#pragma once
#include <string>
#include <vector>
#include <rapidjson/document.h>

std::string parse_ini_value(const std::string& file, const std::string& section, const std::string& key);
std::vector<std::string> parse_filename_from_fileinfo(const std::string& json_str);
std::string parse_filename_after_record(const std::string& json_str);
std::vector<float> parse_wav_to_float(const std::vector<char>& audio_binary);
