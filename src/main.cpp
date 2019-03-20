#include "Logger.h"
#include "SlugColony.h"

#include <curses.h>
#include <string>

static const uint16_t WIDTH = 100;
static const uint16_t HEIGHT = 50;
static const unsigned int HEALTHY_GREEN = 41;

void drawLeaf()
{
    attron(COLOR_PAIR(1));
    for (auto i = 0u; i < HEIGHT; ++i)
    {
        mvhline(i, 0, ' ', WIDTH);
    }
}

enum Move
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void updatePosition(Slug *slug, Move mov)
{
    auto currentPosi = slug->getLeafCoords();
    move(currentPosi.second, currentPosi.first);
    printw(" ");
    if (mov == UP)
    {
        move(currentPosi.second + 1, currentPosi.first);
        printw(" ");
    }
}

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
    drawLeaf();

    SlugColony colony{20};
    std::pair<uint16_t, uint16_t> sizes{WIDTH, HEIGHT};
    colony.createColony(sizes);

    for (auto&& slug : colony.getColony())
    {
        move(slug.getLeafCoords().second, slug.getLeafCoords().first); // TODO: Check why this is inverted
        printw("x");
    }
    

    attroff(COLOR_PAIR(1));
    curs_set(0);
    getch();
    endwin();
}
