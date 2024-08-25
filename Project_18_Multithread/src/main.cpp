#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include <pthread.h>
#include <future>
#include <chrono>
#include <Logging.h>

int global_resource = 0;
std::mutex mutex_lock;

void MessageThread(int param)
{
    int tab = param;
    for(int i=0; i < 10; i++)
    {
        std::lock_guard<std::mutex> guard(mutex_lock);
        if(tab == 1)
            std::cout << "\t 1:Thread - " << global_resource << "\n";
        else if(tab == 2)
            std::cout << "\t\t 2: Thread - " << global_resource << "\n";
        else
            std::cout << "\t\t\t 3: Thread - " << global_resource << "\n";

        global_resource++;
    }
}

int MessageFuture(std::future<int>& param)
{
    int tab = param.get();
    for(int i=0; i < 10; i++)
    {
        if(tab == 4)
            std::cout << "\t\t\t\t 4: Thread - " << global_resource << "\n";

        global_resource++;
    }
    return 0;
}

structlog LOGCFG = {};

int main()
{
    LOG(DEBUG) << "Say hello to this world" << std::endl;
    try
    {
        int x;
        std::promise<int> p;
        std::future<int> f = p.get_future();
        std::future<int> fu = std::async(std::launch::async, MessageFuture, std::ref(f));

        std::vector<std::thread> myThread;
        for(int i = 0; i < 3; i++)
            myThread.emplace_back(MessageThread, i+1);

        // Do something else
        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
        p.set_value(4);
        x = fu.get();

        for(int i = 0; i < 3; i++)
            myThread[i].join();

        std::cout << "Global resource is: " << global_resource << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << "Thread has finished.\n";
    return 0;
}
