#ifndef __CONCURRENCY_DISPATCHER_H__
#define __CONCURRENCY_DISPATCHER_H__

#include <functional>
#include <thread>
#include <vector>

class ConcurrencyDispatcher
{
 public:
    explicit ConcurrencyDispatcher(const std::vector<std::function<void()>>& onFinishCallbacks);
    void beginExecuting(const std::vector<std::function<std::thread()>>& threadSpawners);
    
    void createNew(const std::function<std::thread()> spawner,
        const std::function<void()> killer);

 private:
    void waitForKey();
    void joinThreads();

    std::vector<std::function<void()>> onFinishCallbacks;
    std::vector<std::thread> threads;
    std::thread programTerminator;
};

#endif
