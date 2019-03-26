#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <cstdint>
#include <curses.h>
#include <utility>
#include <vector>

using Coordinates = std::pair<uint16_t, uint16_t>;

class Drawer
{
public:
    static uint16_t colorPair;

    Drawer(uint16_t width, uint16_t height);
    void drawLeaf();
    void drawColony(std::vector<Coordinates>& slugPositions);
    void updatePosition(Coordinates& oldCoords, Coordinates& newCoords);
    void updateLeaf(Coordinates& leafPosition, uint8_t leafSize);
private:
    uint16_t getColorBasedOnLeafSize(uint16_t leafSize);

    uint16_t width;
    uint16_t height;
};

#endif