#include "Drawer.h"
#include "SlugColony.h"
#include "Logger.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const unsigned int HEALTHY_GREEN = 41;
static const uint16_t COLONY_SIZE = 40;


int main()
{
    std::vector<std::thread> threads;
    initscr();
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support colors\n");
        return 1;
    }
    
    start_color();
    init_pair(1, COLOR_BLACK, HEALTHY_GREEN); // TODO: drawer should be the only class that has knowledge about colours

    SlugColony colony{COLONY_SIZE};
    Coordinates sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);

    std::vector<std::vector<std::shared_ptr<Leaf>>> leaves(HEIGHT, std::vector<std::shared_ptr<Leaf>>(WIDTH));
    
    std::vector<Coordinates> startingCoords;
    startingCoords.reserve(COLONY_SIZE);

    auto newColony = colony.getColony();
    for (auto& slug : newColony)
    {
        startingCoords.emplace_back(slug.getLeafCoords());
        slug.setLeaf(leaves[slug.getLeafCoords().first][slug.getLeafCoords().second]);
    }
    auto drawer = std::make_shared<Drawer>(WIDTH, HEIGHT);
    drawer->drawLeaf();
    drawer->drawColony(startingCoords);

    for (auto& slug : newColony)
    {
        threads.emplace_back(slug.spawn(drawer));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    attroff(COLOR_PAIR(1));
    getch();
    endwin();
}
