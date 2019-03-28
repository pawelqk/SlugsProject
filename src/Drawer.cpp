#include "Drawer.h"
#include <stdexcept>

namespace
{
    const uint16_t HEALTHY_GREEN = 41;
    const uint16_t WEAK_GREEN = 44;
}

Drawer::Drawer(uint16_t width, uint16_t height): width(width), height(height)
{
    initscr();
    if (has_colors() == FALSE)
    {
        throw std::runtime_error("Your terminal doesn't support colors. This program will not start");
    }

    initColoring();
}

Drawer::~Drawer()
{
    attroff(COLOR_PAIR(colorPair));
    endwin();
}

void Drawer::drawLeaf()
{
    attron(COLOR_PAIR(1));
    for (auto i = 0u; i < height; ++i)
    {
        mvhline(i, 0, ' ', width);
    }
}

void Drawer::drawColony(std::vector<Coordinates>& slugPositions)
{
    for (auto& position : slugPositions)
    {
        move(position.second, position.first); // TODO: Check why this is inverted
        printw("x");
    }
}

void Drawer::updatePosition(Coordinates& oldCoords, Coordinates& newCoords)
{
    move(oldCoords.second, oldCoords.first);
    printw(" ");
    move(newCoords.second, newCoords.first);
    printw("x");
    curs_set(0);
    refresh();
}

void Drawer::updateLeaf(Coordinates& leafPosition, uint8_t leafSize)    // TODO: this method looks bizarre
{
    uint16_t currentColor = colorPair;
    uint16_t leafColor = getColorBasedOnLeafSize(leafSize);
    attroff(COLOR_PAIR(currentColor));
    attron(COLOR_PAIR(leafColor));
    move(leafPosition.second, leafPosition.first);
    printw("x");
    curs_set(0);
    refresh();
    attroff(COLOR_PAIR(leafColor));
    attron(COLOR_PAIR(currentColor));
}

void Drawer::initColoring()
{
    start_color();
    init_pair(1, COLOR_BLACK, HEALTHY_GREEN);
    init_pair(2, COLOR_BLACK, WEAK_GREEN);
}

uint16_t Drawer::getColorBasedOnLeafSize(uint16_t leafSize)
{
    return 2;
}