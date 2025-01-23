#include <chrono>
#include "src/thread.h"
#include "gtest/gtest.h"

TEST(Addition_1, TestCase_1)
{
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // ------------------------------- START --------------------------------------------- //
    
    int threadCount = std::thread::hardware_concurrency();
    EXPECT_EQ(init(5000), 5000*threadCount);
    
    //EXPECT_EQ(init(3000), 5000*threadCount);

    // -------------------------------- END ---------------------------------------------- //

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Output the duration in microseconds
    std::cout << "Time taken by code snippet: " << duration.count() << " microseconds" << std::endl;
}

TEST(Addition_2, TestCase_2)
{
    int threadCount = std::thread::hardware_concurrency();
    EXPECT_EQ(init(50000), 50000*threadCount);
}

/*int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/