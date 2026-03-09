#include "HttpClient.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Parser.h"
#include <mutex>

std::vector<std::string> HttpClient::get_file_info()
{
    std::string response;
    std::string FILEINFO_URL = this->BASE_URL + this->FILE_PORT + this->FILEINFO_ENDPOINT;
    std::vector<std::string> filename_list;
    
    curl_easy_setopt(this->recorder_curl, CURLOPT_URL,
            FILEINFO_URL.c_str()); // GET REQUEST 

    curl_easy_setopt(this->recorder_curl, CURLOPT_WRITEFUNCTION, Fileinfo_Callback);
    curl_easy_setopt(this->recorder_curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(this->recorder_curl);

    if (res != CURLE_OK)
    {
        std::cout << "curl failed during GET: " << curl_easy_strerror(res) << std::endl;
        return filename_list;
    }

    filename_list = parse_filename_from_fileinfo(response);
    return filename_list;
}

std::string HttpClient::post_record_command()
{   
    std::string recorded_filename;

    std::string url =
        this->BASE_URL +
        this->ACTION_PORT +
        this->MEASUREMENT_ENDPOINT;

    std::string payload = R"({
            "dataProvider": {
                "type": "Source",
                "id" : 1,
                "channels" : "Separate"
            },
            "properties" : {
                "type": "Data",
                "format" : "Wav",
                "duration" : 1000000000,
                "fileName" : "SC2_record"
            },
            "tag": "Leq measurement 1"
    })";

    curl_easy_setopt(this->recorder_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->recorder_curl, CURLOPT_POST, 1L);
    curl_easy_setopt(this->recorder_curl, CURLOPT_TIMEOUT, 2L);
    curl_easy_setopt(this->recorder_curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(this->recorder_curl, CURLOPT_POSTFIELDSIZE, payload.size());

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "accept: application/json");
    curl_easy_setopt(this->recorder_curl, CURLOPT_HTTPHEADER, headers);

    std::string response;
    curl_easy_setopt(this->recorder_curl, CURLOPT_WRITEFUNCTION, Fileinfo_Callback);
    curl_easy_setopt(this->recorder_curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(this->recorder_curl);

    if (res != CURLE_OK)
    {
        std::cout << "curl failed during POST: " << curl_easy_strerror(res) << std::endl;
        return recorded_filename;
    }

    long http_code = 0;
    curl_easy_getinfo(this->recorder_curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    if (http_code == 200)
    {
        recorded_filename = parse_filename_after_record(response);
    }
    curl_slist_free_all(headers);
    curl_easy_setopt(this->recorder_curl, CURLOPT_POST, 0L);

    return recorded_filename;
}

std::vector<char> HttpClient::get_audio_file(const std::string& filename)
{   
    std::vector<char> audio_binary;
    std::string url = this->BASE_URL 
                    + this->FILE_PORT
                    + this->DOWNLOAD_ENDPOINT
                    + "?path=" + filename;

    curl_easy_setopt(this->download_curl, CURLOPT_URL,
        url.c_str());

    curl_easy_setopt(this->download_curl, CURLOPT_WRITEFUNCTION, RecordAudio_Callback);
    curl_easy_setopt(this->download_curl, CURLOPT_WRITEDATA, &audio_binary);

    CURLcode res = curl_easy_perform(this->download_curl);

    if (res != CURLE_OK)
    {
        std::cout << "curl failed during GET: " << curl_easy_strerror(res) << std::endl;
        return audio_binary;
    }

    long http_code = 0;
    curl_easy_getinfo(this->download_curl, CURLINFO_RESPONSE_CODE, &http_code);

    return audio_binary;
}

int HttpClient::delete_audio_file(const std::string& filename)
{
    std::string url =
        this->BASE_URL +
        this->FILE_PORT +
        this->DELETE_ENDPOINT +
        "?path=" + filename;

    curl_easy_setopt(this->download_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->download_curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    CURLcode res = curl_easy_perform(this->download_curl);

    if (res != CURLE_OK)
    {
        std::cout << "curl failed during DELETE: "
            << curl_easy_strerror(res) << std::endl;
        return -1;
    }

    curl_easy_setopt(this->download_curl, CURLOPT_CUSTOMREQUEST, NULL);
    return 0;
}

size_t HttpClient::Fileinfo_Callback(void* contents, size_t size, size_t nmemb, void* userp)
{   
    size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

size_t HttpClient::RecordAudio_Callback(void* contents, size_t size, size_t nmemb, void* userp)
{   
    size_t totalSize = size * nmemb;

    std::vector<char>* buffer =
        static_cast<std::vector<char>*>(userp);

    char* data = static_cast<char*>(contents);

    buffer->insert(buffer->end(), data, data + totalSize);

    return totalSize;

}

HttpClient::HttpClient(const std::string& IP, const std::string& username, const std::string& pwd)
{   
    this->BASE_IP = IP;
    this->BASE_URL = "http://" + IP;
    this->USERNAME = username;
    this->PWD = pwd;

    this->check_network();

    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->recorder_curl = curl_easy_init();
    this->download_curl = curl_easy_init();

    curl_easy_setopt(this->recorder_curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(this->recorder_curl, CURLOPT_PASSWORD, pwd.c_str());

    curl_easy_setopt(this->download_curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(this->download_curl, CURLOPT_PASSWORD, pwd.c_str());

}

void HttpClient::check_network()
{   
    std::string cmd =
        "ping -n 1 -w 1000 " + this->BASE_IP + " > nul";


    while (!(system(cmd.c_str()) == 0))
    {
        std::cout << "Waiting for Sorama on " << this->BASE_IP << "..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::cout << "Can reach Sorama" << std::endl;
}
