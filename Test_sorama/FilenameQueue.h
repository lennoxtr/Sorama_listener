#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class FilenameQueue
{
    private:
        std::queue<std::string> queue_;
        std::mutex mutex_;
        std::condition_variable cv_;
        bool stop_ = false;

    public:
        void push(const std::string& filename) {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(filename);
            }
            cv_.notify_one(); 
        }

        std::string pop() {
            std::string filename;
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return !queue_.empty() || stop_; });

            if (stop_ && queue_.empty())
                return filename;

            filename = queue_.front();
            queue_.pop();
            return filename;
        }

        void stop() {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                stop_ = true;
            }
            cv_.notify_all();
        }
};

