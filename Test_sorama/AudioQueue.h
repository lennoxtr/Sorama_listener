#pragma once
#include <vector>
#include <atomic>
#include <algorithm>
#include <cstddef>

class AudioQueue {
public:
    AudioQueue(size_t capacity)
        : buffer_(capacity), capacity_(capacity),
        readPos_(0), writePos_(0) {
    }

    size_t push(const float* data, size_t frames) {
        size_t written = 0;
        for (size_t i = 0; i < frames; ++i) {
            size_t next = (writePos_ + 1) % capacity_;
            if (next == readPos_.load(std::memory_order_acquire))
                break; // buffer full
            buffer_[writePos_] = data[i];
            writePos_ = next;
            ++written;
        }
        return written;
    }

    size_t pop(float* out, size_t frames) {
        size_t read = 0;
        for (size_t i = 0; i < frames; ++i) {
            if (readPos_.load(std::memory_order_acquire) == writePos_)
                break; // buffer empty
            out[i] = buffer_[readPos_];
            readPos_ = (readPos_ + 1) % capacity_;
            ++read;
        }
        return read;
    }

    size_t size() const {
        if (writePos_ >= readPos_)
            return writePos_ - readPos_;
        else
            return capacity_ - readPos_ + writePos_;
    }

    size_t remaining() const { return capacity_ - 1 - size(); }

private:
    std::vector<float> buffer_;
    size_t capacity_;
    std::atomic<size_t> readPos_;
    std::atomic<size_t> writePos_;
};