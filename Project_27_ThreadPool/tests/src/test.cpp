#include <chrono>

#include "icecream.hpp"
#include "gtest/gtest.h"

#include "src/ThreadPool.h"

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

TEST_F(UnitTestFixture, TestCase_1)
{
    // 1. Test default ThreadPool
    ThreadPool myPool0;
    std::future<int>res = myPool0.PushTask(Func,2);
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    //EXPECT_EQ(res.get(), 4);
    std::future<int>res3 = myPool0.PushTask(Func,3);
    std::future<int>res4 = myPool0.PushTask(Func,4);
    std::future<int>res5 = myPool0.PushTask(Func,5);
    std::future<int>res6 = myPool0.PushTask(Func,6);
    std::future<int>res7 = myPool0.PushTask(Func,7);
    std::future<int>res8 = myPool0.PushTask(Func,8);
    std::future<int>res9 = myPool0.PushTask(Func,9);

    // Excess tasks on queue
    std::future<int>res10 = myPool0.PushTask(Func,10);
    std::future<int>res11 = myPool0.PushTask(Func,11);
    std::future<int>res12 = myPool0.PushTask(Func,12);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Remaining items on queue now: " << myPool0.QueueItems() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20000));
}

TEST_F(UnitTestFixture, TestCase_2)
{
    // 2. Test ThreadPool with specific size
    ThreadPool myPool1(16);
    std::future<int>res2 = myPool1.PushTask([](const int& a){
            std::cout<<"This is from Lambda Function \n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return a*a;
        }, 6);
    EXPECT_EQ(res2.get(), 36);
}
} // Namespace