#include <iostream>
#include "Logging.h"
#include <vector>
#include <thread>

structlog LOGCFG = {};

int main()
{
    std::cout << "Main thread has run.\n";

    std::vector<std::thread> myThreads;
    for(int i=0; i < 2; i++)
    {
        myThreads.emplace_back([i](int threadNum){
            int x = 15;
            while(x > 0)
            {
                LOG(DEBUG) << "Thread #" << i << " is printing.\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                x--;
            }
        },
        i);
    }

    LOG(WARN) << "This is my test." << std::endl;
    LOG(ERROR) << "This is my 2nd test." << std::endl;
    LOG(DEBUG) << "This is my 3rd test." << std::endl;
    LOG(INFO) << "This is my 4th test." << " I am not done yet." << std::endl;
    LOG(INFO) << "Writing numbers: " << 2 << 3.0f << 1.0e2 << std::endl;

    std::cout << "Not yet end of life.\n";

    for(auto& thread: myThreads)
        thread.join();
    return 0;
}
