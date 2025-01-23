#pragma once

#include <thread>
#include <mutex>
#include <atomic>

class ThreadID { 
    std::thread::id id;
    inline static std::mutex mut;
    int loops;
public:
    ThreadID(const int& loop) : id{ std::this_thread::get_id() }, loops{ loop } {
        //std::cerr << "Launched thread: " << id << '\n';
    }

    void process(std::atomic<int>& cntr);
    ~ThreadID();
};

int init(const int& loop);