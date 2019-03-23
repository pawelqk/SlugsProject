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
    init_pair(1, COLOR_BLACK, HEALTHY_GREEN);

    SlugColony colony{COLONY_SIZE};
    Coordinates sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);
    
    std::vector<Coordinates> startingCoords;
    startingCoords.reserve(COLONY_SIZE);
    for (auto& slug : colony.getColony())
    {
        startingCoords.emplace_back(slug.getLeafCoords());
    }
    auto drawer = std::make_shared<Drawer>(WIDTH, HEIGHT);
    drawer->drawLeaf();
    drawer->drawColony(startingCoords);
    auto newColony = colony.getColony();

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
