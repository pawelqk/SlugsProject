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

void Drawer::drawColony(SlugColony& colony)
{
    for (auto&& slug : colony.getColony())
    {
        move(slug.getLeafCoords().second, slug.getLeafCoords().first); // TODO: Check why this is inverted
        printw("x");
    }
}

void Drawer::updatePosition(Slug slug, Coordinates oldPosition)
{
    auto& currentPosi = slug.getLeafCoords();
    move(oldPosition.second, oldPosition.first);
    printw(" ");
    move(currentPosi.second, currentPosi.first);
    printw("x");
}