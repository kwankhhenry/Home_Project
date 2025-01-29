#include <chrono>

#include "icecream.hpp"
#include "gtest/gtest.h"

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
    template<typename T, int samples>
    constexpr void BenchMarkCompile(const T& obj, const std::string& name){
        //auto start = std::chrono::high_resolution_clock::now();

        // <-------------- Implementation ------------------>


        // <---------- End of Implementation ------------------>

        //auto stop = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // IC Output
        //IC(name, results, duration);
    }
};

TEST_F(UnitTestFixture, CompileTime_TestCases)
{

}

TEST_F(UnitTestFixture, RunTime_TestCases)
{

}
} // Namespace