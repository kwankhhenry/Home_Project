#include <iostream>
#include <chrono>

// Function to calculate the length of a string
int length(const std::string& X) {
    return X.length();
}

// constexpr function to calculate the length of a string literal
constexpr std::size_t strlen_constexpr(const char* str) {
    return *str ? 1 + strlen_constexpr(str + 1) : 0;
}

int main() { 
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // ------------------------------- START --------------------------------------------- //

    constexpr const char helloWorld[] = "Hello, world!";
    constexpr std::size_t length = strlen_constexpr(helloWorld);
    std::cout << "Length of 'Hello, world!': " << length << std::endl;

    // -------------------------------- END ---------------------------------------------- //

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Output the duration in microseconds
    std::cout << "Time taken by code snippet: " << duration.count() << " microseconds" << std::endl;

    return 0;
}