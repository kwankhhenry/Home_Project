#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>

#include "icecream.hpp"
#include "random_pi.h"

int main() { 
    RandomPiRunTime random_pi;
    IC();

    for(int i = 0; i < 100000; i++){
        random_pi.AddSample();
    }

    IC(random_pi.GetResult());

    return 0;
}