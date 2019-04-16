#include "Drawer.h"
#include "SlugColony.h"

#include <curses.h>
#include <iostream>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const uint16_t COLONY_SIZE = 2;

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
    }


    auto leafField = std::make_shared<LeafField>(sizes, colony);

    auto drawerThread = mainDrawer->spawnRefreshingThread(leafField->getLeaves());
    auto rebuildThread = leafField->spawnRebuildingThread();
    auto waitForEnd = [&]()
    {
        while (getch() != ' ') {}
        colony->end();
        leafField->end();
        mainDrawer->end();
        attroff(COLOR_PAIR(1));
        refresh();
        endwin();
    };
    auto finishingThread = std::thread(waitForEnd);
    for (auto& slug : newColony)
    {
        threads.push_back(slug.second.spawn(mainDrawer));
    }


    rebuildThread.join();
    drawerThread.join();
    finishingThread.join();
    for (auto& thread : threads)
    {
        thread.join();
    }
}
