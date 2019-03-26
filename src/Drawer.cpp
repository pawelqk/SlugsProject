#include "Drawer.h"


Drawer::Drawer(uint16_t width, uint16_t height): width(width), height(height)
{}

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
    // attroff(COLOR_PAIR(currentColor));
    attron(leafColor);
    move(leafPosition.second, leafPosition.first);
    printw(" ");
    curs_set(0);
    refresh();
    // attroff(leafColor);
    attron(currentColor);
}

uint16_t Drawer::getColorBasedOnLeafSize(uint16_t leafSize)
{
    return 2;
}