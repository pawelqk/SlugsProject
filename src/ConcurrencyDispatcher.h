#include <functional>
#include <thread>
#include <vector>


class ConcurrencyDispatcher
{
 public:
    explicit ConcurrencyDispatcher(const std::vector<std::function<void()>>& onFinishCallbacks);
    void beginExecuting(const std::vector<std::function<std::thread()>>& threadSpawners);

 private:
    void waitForKey();
    void joinThreads();

    std::vector<std::function<void()>> onFinishCallbacks;
    std::vector<std::thread> threads;
    std::thread programTerminator;
};
