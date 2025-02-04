#include <format>
#include <string>
#include <chrono>
#include "normal_interface.h"
#include "crtp_interface.h"

#include "icecream.hpp"

template <typename T, typename S>
void Benchmark(T& object, S function, const std::string& name)
{
    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    // Execute the function
    function(&object);

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate time and output result
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    IC(name, duration);
}

template <typename S>
constexpr void BenchmarkCompile(S function, const std::string& name)
{
    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    // Execute the function
    function();

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate time and output result
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    IC(name, duration);
} 

int main()
{
    NormalImplemented object_1;
    Benchmark(object_1, RunNormal, "Normal Interface");

    BenchmarkCompile(RunCRTP<CRTPImplemented, 1300>, "CRTP Interface");

    return 0;
}