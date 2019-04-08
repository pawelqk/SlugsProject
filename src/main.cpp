#include "Drawer.h"
#include "SlugColony.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const uint16_t COLONY_SIZE = 20;

int main()
{
    std::vector<std::thread> threads;
    std::shared_ptr<Drawer> mainDrawer;
    try
    {
        mainDrawer = std::make_shared<Drawer>(WIDTH, HEIGHT);
    }
    catch (std::runtime_error& er)
    {
        return 1;
    }

    SlugColony colony{COLONY_SIZE};
    Coordinates sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);
    
    std::vector<Coordinates> startingCoords;
    startingCoords.reserve(COLONY_SIZE);

    auto newColony = colony.getColony();    
    for (auto& slug : newColony)
    {
        startingCoords.emplace_back(slug.getLeafCoords());
    }

    auto leafField = colony.getLeafField()->getLeaves();

    auto drawerThread = mainDrawer->spawnRefreshingThread(leafField);
    auto rebuildThread = colony.getLeafField()->spawnRebuildingThread();
    for (auto& slug : newColony)
    {
        threads.push_back(slug.spawn(mainDrawer));
    }

    rebuildThread.join();
    drawerThread.join();
    for (auto& thread : threads)
    {
        thread.join();
    }

    getch();
}
