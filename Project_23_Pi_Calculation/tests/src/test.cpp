#include <chrono>

#include "icecream.hpp"
#include "gtest/gtest.h"

#include "src/random_pi.h"

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

        T temp_obj = obj; // Create a temporary copy to modify
        // <-------------- Implementation ------------------>
        for(size_t i = 0; i < samples; ++i){
            temp_obj.AddSample();
        }
        auto result = temp_obj.GetResult();
        EXPECT_EQ(result > 3.0f && result < 3.25f, true);
        //static_assert(result > 3.0f && result < 3.25f, "Pi value is out of range!");

        // <---------- End of Implementation ------------------>

        //auto stop = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // IC Output
        IC(name, result);
        //IC(name, results, duration);
    }

    // Helper function to benchmark individual function call
    template<typename T, int samples>
    void BenchMarkRun(T& obj, const std::string& name){
        //auto start = std::chrono::high_resolution_clock::now();

        // <-------------- Implementation ------------------>
        for(size_t i = 0; i < samples; ++i){
            obj.AddSample();
        }
        auto result = obj.GetResult();
        EXPECT_EQ(result > 3.0f && result < 3.25f, true);

        // <---------- End of Implementation ------------------>

        //auto stop = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // IC Output
        IC(name, result);
        //IC(name, result, duration);
    }
};

TEST_F(UnitTestFixture, CompileTime_TestCases)
{
    constexpr RandomPiCompileTime<100> random_pi;
    BenchMarkCompile<RandomPiCompileTime<100>, 100>(random_pi, "Compile-Time Random Pi with 100 Samples");

    constexpr RandomPiCompileTime<1000> random_pi2;
    BenchMarkCompile<RandomPiCompileTime<1000>, 1000>(random_pi2, "Compile-Time Random Pi with 1000 Samples");

    constexpr RandomPiCompileTime<10000> random_pi3;
    BenchMarkCompile<RandomPiCompileTime<10000>, 10000>(random_pi3, "Compile-Time Random Pi with 10000 Samples");
}

TEST_F(UnitTestFixture, RunTime_TestCases)
{
    RandomPiRunTime random_pi;
    BenchMarkRun<RandomPiRunTime, 100>(random_pi, "Run-Time Random Pi with 100 Samples");
    BenchMarkRun<RandomPiRunTime, 1000>(random_pi, "Run-Time Random Pi with 1000 Samples");
    BenchMarkRun<RandomPiRunTime, 10000>(random_pi, "Run-Time Random Pi with 10000 Samples");
}
} // Namespace