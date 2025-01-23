#include <vector>
#include "thread.h"

void ThreadID::process(std::atomic<int>& cntr){
    //std::lock_guard<std::mutex> lock(mut);
    int local = 0;
    for(int i = 0; i < loops; i++)
        local++;
    
    cntr.fetch_add(local, std::memory_order_relaxed);    
}

ThreadID::~ThreadID(){
    //std::lock_guard<std::mutex> lock(mut);
    //std::cerr << "Finished thread: " << id << '\n';
}