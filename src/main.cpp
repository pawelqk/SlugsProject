#include "Drawer.h"
#include "SlugColony.h"
// #include "Logger.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const uint16_t COLONY_SIZE = 100;

int main()
{
    // Logger logger("main");
    std::vector<std::thread> threads;
    std::shared_ptr<Drawer> mainDrawer;
    try
    {   // TODO: check on wrong terminal if it works
        mainDrawer = std::make_shared<Drawer>(WIDTH, HEIGHT);
    }
    catch (std::runtime_error& er)
    {
        // logger(ERROR) << er.what() << std::endl;
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
        // slug.setLeaf(leaves[slug.getLeafCoords().second][slug.getLeafCoords().first]);  
    }

    auto leafField = colony.getLeafField()->getLeaves();
    auto drawerThread = mainDrawer->spawnRefreshingThread(leafField);

    for (auto& slug : newColony)
    {
        threads.push_back(slug.spawn(mainDrawer));
    }

    drawerThread.join();
    for (auto& thread : threads)
    {
        thread.join();
    }

    getch();
}
