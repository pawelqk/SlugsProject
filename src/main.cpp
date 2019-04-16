#include "ConcurrencyDispatcher.h"
#include "Drawer.h"
#include "SlugColony.h"

#include <curses.h>
#include <iostream>
#include <string>

namespace
{
    constexpr uint16_t WIDTH = 100;
    constexpr uint16_t HEIGHT = 40;
    constexpr uint16_t COLONY_SIZE = 2;
}

int main()
{
    std::vector<std::thread> threads;
    Coordinates sizes{WIDTH, HEIGHT};
    auto colony = std::make_shared<SlugColony>(COLONY_SIZE, sizes);
    std::shared_ptr<Drawer> mainDrawer;
    try
    {
        mainDrawer = std::make_shared<Drawer>(WIDTH, HEIGHT, colony);
    }
    catch (std::runtime_error& er)
    {
        return 1;
    }
    std::vector<Coordinates> startingCoords;
    startingCoords.reserve(COLONY_SIZE);

    auto& newColony = colony->getColony();
    for (auto& slug : newColony)
    {
        startingCoords.emplace_back(slug.second.getLeafCoords());
        slug.second.setDrawer(mainDrawer);
    }

    auto leafField = std::make_shared<LeafField>(sizes, colony);
    mainDrawer->setLeaves(leafField->getLeaves());

    std::vector<std::function<void()>> onFinishCallbacks{
        std::bind(&SlugColony::end, colony.get()),
        std::bind(&LeafField::end, leafField.get()),
        std::bind(&Drawer::end, mainDrawer.get())};
    std::vector<std::function<std::thread()>> threadSpawners{
        std::bind(&Drawer::spawnRefreshingThread, mainDrawer),
        std::bind(&LeafField::spawnRebuildingThread, leafField)};
    for (auto& slug : newColony)
    {
        onFinishCallbacks.push_back(slug.second.receiveKiller());
        threadSpawners.push_back(slug.second.receiveSpawner());
    }

    ConcurrencyDispatcher concurrencyDispatcher{onFinishCallbacks};
    concurrencyDispatcher.beginExecuting(threadSpawners);
}
