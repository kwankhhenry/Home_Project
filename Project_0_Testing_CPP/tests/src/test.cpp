#include <chrono>

#include "icecream.hpp"
#include "gtest/gtest.h"

#include "src/thread.h"

namespace UnitTests{

// Define fixture for unit testing
class UnitTestFixture: public testing::Test{

private:
    // Declares the variables your tests want to use.
    std::chrono::_V2::system_clock::time_point testStart, testStop;
    std::chrono::microseconds testDuration;

protected:  // You should make the members protected s.t. they can be accessed from sub-classes.
    
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    void SetUp() override {
        // Start the timer
        testStart = std::chrono::high_resolution_clock::now();
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
        // Stop the timer
        testStop = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        testDuration = std::chrono::duration_cast<std::chrono::microseconds>(testStop - testStart);

        // Output the duration in microseconds
        std::cout << "Time taken by entire code snippet: " << testDuration << std::endl;
    }

    // A helper function that some test uses.
    static int Func(int a)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return a*a; 
    }

public:
    // Helper function to benchmark individual function call
    int init(const int& loop){
        std::vector<std::thread> threads;
        unsigned threadCount = (std::thread::hardware_concurrency() < 2) ? 1 : std::thread::hardware_concurrency();
        for (int t = 0; t != threadCount; ++t) {
            threads.emplace_back(&ThreadID::process, ThreadID(loop), std::ref(counter));
        }

        for (auto& t : threads) {
            t.join();
        }
        IC(counter);
        return counter;
    }

    std::atomic<int> counter{0};
};

TEST_F(UnitTestFixture, TestCase_1)
{
    int threadCount = std::thread::hardware_concurrency();
    EXPECT_EQ(init(5000), 5000*threadCount);
    EXPECT_EQ(init(5000), 5000*threadCount);
    //EXPECT_EQ(init(3000), 5000*threadCount);
    EXPECT_EQ(init(5000), 5000*threadCount);
    EXPECT_EQ(init(5000), 5000*threadCount);
}

TEST_F(UnitTestFixture, TestCase_2)
{
    int threadCount = std::thread::hardware_concurrency();
    EXPECT_EQ(init(50000), 50000*threadCount);
}
}