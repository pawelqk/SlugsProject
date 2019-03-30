#include "Drawer.h"
#include "SlugColony.h"
#include "Logger.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const uint16_t COLONY_SIZE = 10;

int main()
{
    std::vector<std::thread> threads;
    std::shared_ptr<Drawer> mainDrawer;
    try
    {   // TODO: check on wrong terminal if it works
        mainDrawer = std::make_shared<Drawer>(WIDTH, HEIGHT);
    }
    catch (std::runtime_error& er)
    {
        std::cout << er.what() << std::endl;
        return 1;
    }

    SlugColony colony{COLONY_SIZE};
    Coordinates sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);

    std::vector<std::vector<std::shared_ptr<Leaf>>> leaves(HEIGHT, std::vector<std::shared_ptr<Leaf>>(WIDTH, std::make_shared<Leaf>()));
    
    std::vector<Coordinates> startingCoords;
    startingCoords.reserve(COLONY_SIZE);

    auto newColony = colony.getColony();
    for (auto& slug : newColony)
    {
        startingCoords.emplace_back(slug.getLeafCoords());
        slug.setLeaf(leaves[slug.getLeafCoords().second][slug.getLeafCoords().first]);  
    }
    mainDrawer->drawLeaf();
    mainDrawer->drawColony(startingCoords);

    for (auto& slug : newColony)
    {
        threads.emplace_back(slug.spawn(mainDrawer));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    getch();
}
