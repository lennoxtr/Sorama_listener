#pragma once
#include <curl/curl.h>
#include <string>
#include <vector>

class HttpClient
{	
	private:
		std::string BASE_IP;
		std::string BASE_URL;
		std::string USERNAME;
		std::string PWD;
		int RECORDING_TIME;

		const std::string FILE_PORT = ":9013";
		const std::string ACTION_PORT = ":9011";
		const std::string FILEINFO_ENDPOINT = "/fileinfo";
		const std::string DOWNLOAD_ENDPOINT = "/file";
		const std::string DELETE_ENDPOINT = "/file";
		const std::string MEASUREMENT_ENDPOINT = "/measurements";

		CURL* recorder_curl;
		CURL* download_curl;

		static size_t Fileinfo_Callback(void* contents, size_t size, size_t nmemb, void* userp);
		static size_t RecordAudio_Callback(void* contents, size_t size, size_t nmemb, void* userp);

	public:
		HttpClient(const std::string& IP, const std::string& username, const std::string& pwd, int recording_time);
		void check_network();

		// HTTP Related Commands
		std::vector<std::string> get_file_info();
		std::string post_record_command();
		std::vector<char> get_audio_file(const std::string& filename);
		int delete_audio_file(const std::string& filename);
};

