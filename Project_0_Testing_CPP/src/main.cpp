#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>

#include "thread.h"

std::atomic<int> counter{0};

int init(const int& loop){
    std::vector<std::thread> threads;
    //std::cout << "Max hardware concurrency is: " << std::thread::hardware_concurrency() << std::endl;
    unsigned threadCount = (std::thread::hardware_concurrency() < 2) ? 1 : std::thread::hardware_concurrency();
    for (int t = 0; t != threadCount; ++t) {
        threads.emplace_back(&ThreadID::process, ThreadID(loop), std::ref(counter));
    }
    for (auto& t : threads) {
        t.join();
    }
    //std::cout << "std::hardware_destructive_interference_size is: " << std::hardware_destructive_interference_size << std::endl;
    //std::cout << "Counter is: " << counter << std::endl;
    return counter;
}

int main() { 
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // ------------------------------- START --------------------------------------------- //
    std::cout << init(50000) << std::endl;
    std::cout << init(3000) << std::endl;
    // -------------------------------- END ---------------------------------------------- //

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Output the duration in microseconds
    std::cout << "Time taken by code snippet: " << duration.count() << " microseconds" << std::endl;

    return 0;
}