#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>

#include "thread.h"

int main() { 
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // ------------------------------- START --------------------------------------------- //
    //std::cout << init(50000) << std::endl;
    //std::cout << init(3000) << std::endl;
    // -------------------------------- END ---------------------------------------------- //

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Output the duration in microseconds
    std::cout << "Time taken by code snippet: " << duration.count() << " microseconds" << std::endl;

    return 0;
}