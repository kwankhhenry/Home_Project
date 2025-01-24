#pragma once

#include <vector>
#include <random>

template<size_t N>
class RandomPiCompileTime{
public:
    constexpr RandomPiCompileTime(){
        seed_array = generate_random_sequence(seed);
    }

    constexpr void AddSample(){
        // Compile-time generation
        uint32_t seed_x = NextSeed(seed_array[samples]);
        uint32_t seed_y = NextSeed(seed_x);
        float x = static_cast<float>(Random(seed_x)) / 1000.0f;
        float y = static_cast<float>(Random(seed_y)) / 1000.0f;

        float distance = x * x + y *  y;
        if(distance < 1.0){
            ++samples_inside_circle;
        }
        ++samples;
    }

    constexpr float GetResult() const {
        float result = 4.0 * static_cast<float>(samples_inside_circle) / static_cast<float>(samples);
        return result;
    }

private:
    // Recursive function to fill an array with pseudo-random numbers at compile-time
    constexpr std::array<int, N> generate_random_sequence(int seed) {
        std::array<int, N> arr = {};
        for (std::size_t i = 0; i < N; ++i) {
            arr[i] = Random(seed + i); // Using a changing seed to generate different numbers
        }
        return arr;
    }

    // Compile-time pseudo-random number generator
    constexpr uint32_t Random(uint32_t value) const {
        return ((value * 1664525u + 1013904223u) & 0xFFFFFFFF) % 1001;
    }

    // Get the next seed
    constexpr uint32_t NextSeed(uint32_t current_seed) const {
        return Random(current_seed);
    }

    int samples = 0;
    int samples_inside_circle = 0;
    uint32_t seed = 49;                 // Fixed initial seed for deterministic behavior
    std::array<int, N> seed_array;
};

class RandomPiRunTime{
public:
    RandomPiRunTime(){
        rng = std::mt19937(dev());
        dist = std::uniform_int_distribution<std::mt19937::result_type>(1,1000);
    }

    void AddSample(){
        // Run-time generation
        float x = GetRandomNumber();
        float y = GetRandomNumber();

        float distance = x * x + y *  y;
        if(distance < 1.0){
            ++samples_inside_circle;
        }
        ++samples;
    }

    float GetResult() {
        float result = 4.0 * static_cast<float>(samples_inside_circle) / static_cast<float>(samples);
        return result;
    }

private:
    // Run-time random number generator
    float GetRandomNumber(){
        float result = dist(rng)/ 1000.0f;
        return result;
    }

    int samples = 0;
    int samples_inside_circle = 0;

    // Random number generator created only once upon class construction
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;
};