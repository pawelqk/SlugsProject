#include "Drawer.h"
#include "SlugColony.h"
#include "Logger.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 40;
static const unsigned int HEALTHY_GREEN = 41;
static const uint16_t COLONY_SIZE = 5;

int main()
{
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
    std::pair<uint16_t, uint16_t> sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);
    
    Drawer drawer{WIDTH, HEIGHT};
    drawer.drawLeaf();
    drawer.drawColony(colony);

    auto newColony = colony.getColony();
    for (auto&& slug : newColony)
    {
        drawer.updatePosition(slug, slug.moveRandomly(sizes));
    }
    colony.setColony(newColony);
    

    attroff(COLOR_PAIR(1));
    curs_set(0);
    getch();
    endwin();
}
