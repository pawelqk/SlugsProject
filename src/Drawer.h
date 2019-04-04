#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "LeafField.h"
// #include "Logger.h"

#include <cstdint>
#include <curses.h>
#include <utility>
#include <vector>
#include <thread>   

using Coordinates = std::pair<uint16_t, uint16_t>;

class Drawer
{
public:
    Drawer(uint16_t width, uint16_t height);
    ~Drawer();
    void drawLeaf();
    void drawColony(std::vector<Coordinates>& slugPositions);
    void updatePosition(Coordinates& oldCoords, Coordinates& newCoords);
    void updateLeaf(Coordinates& leafPosition, uint8_t leafSize);

    std::thread spawnRefreshingThread(LeafMatrix& leaves);
private:
    void refreshScreen();
    void initColoring();
    uint16_t getColorBasedOnLeafSize(uint16_t leafSize);

    LeafMatrix leaves;
    uint16_t width;
    uint16_t height;

    // Logger logger;
};

#endif