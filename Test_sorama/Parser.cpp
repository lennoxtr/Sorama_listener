#include <string>
#include <Windows.h>
#include <iostream>
#include "Parser.h"
#include <rapidjson/document.h>
#include <sndfile.h>

std::string parse_ini_value(const std::string& file, const std::string& section, const std::string& key) {
    char buffer[128];
    DWORD len = GetPrivateProfileStringA(section.c_str(), key.c_str(), "", buffer, sizeof(buffer), file.c_str());
    std::string value(buffer, len);
    
    if (!value.empty() && value.front() == '"' && value.back() == '"')
        value = value.substr(1, value.size() - 2);
    return value;
}

std::vector<std::string> parse_filename_from_fileinfo(const std::string& json_str)
{   
    std::vector<std::string> paths;
    rapidjson::Document doc;

    if (doc.Parse(json_str.c_str()).HasParseError())
    {
        std::cout << "JSON parse error after fileinfo\n";
        return paths;
    }

    for (rapidjson::SizeType i = 0; i < doc.Size(); i++)
    {
        const rapidjson::Value& file = doc[i];

        if (file.HasMember("path"))
        {
            paths.push_back(file["path"].GetString());
        }
    }

    return paths;
}

std::string parse_filename_after_record(const std::string& json_str)
{
    std::string filename;

    rapidjson::Document doc;

    if (doc.Parse(json_str.c_str()).HasParseError())
    {
        std::cout << "JSON parse error after record\n";
        return filename;
    }

    filename = doc["settings"]["properties"]["fileName"].GetString();
    return filename;
}

std::vector<float> parse_wav_to_float(const std::vector<char>& audio_binary)
{
    std::vector<float> float_buffer;

    // Each sample is 4 bytes
    if (audio_binary.size() % 4 != 0)
        return float_buffer;

    size_t n_samples = audio_binary.size() / 4;
    float_buffer.reserve(n_samples);

    for (size_t i = 0; i < n_samples; ++i)
    {
        float sample;
        std::memcpy(&sample, &audio_binary[i * 4], sizeof(float));
        float_buffer.push_back(sample); // already in [-1.0f, 1.0f]
    }

    return float_buffer;
}
