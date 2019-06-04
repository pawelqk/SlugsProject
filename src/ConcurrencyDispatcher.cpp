#include "ConcurrencyDispatcher.h"

#include <curses.h>
#include <iostream>

namespace
{
    constexpr char FINISHER = ' ';
}

ConcurrencyDispatcher::ConcurrencyDispatcher(
    const std::vector<std::function<void()>>& onFinishCallbacks)
{
    this->onFinishCallbacks = onFinishCallbacks;
    programTerminator = std::thread([this](){ waitForKey(); });
}

void ConcurrencyDispatcher::beginExecuting(
    const std::vector<std::function<std::thread()>>& threadSpawners)
{
    threads.reserve(threadSpawners.size());
    for (auto& spawner : threadSpawners)
    {
        threads.push_back(spawner());
    }
    joinThreads();
}

void ConcurrencyDispatcher::joinThreads()
{
    for (auto& thread : threads)
    {
        thread.detach();
    }
    programTerminator.join();
}

void ConcurrencyDispatcher::waitForKey()
{
    while (getch() != FINISHER) {}
    for (auto& callback : onFinishCallbacks)
    {
        callback();
    }
}

void ConcurrencyDispatcher::createNew(const std::function<std::thread()> spawner,
    const std::function<void()> killer)
{
    onFinishCallbacks.push_back(killer);
    auto thread = spawner();
    thread.detach();
}
