#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "LeafField.h"

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
    void drawColony(const std::vector<Coordinates>& slugPositions);
    void updatePosition(const Coordinates& oldCoords, const Coordinates& newCoords);
    void updateLeaf(const Coordinates& leafPosition, uint8_t leafSize);

    std::thread spawnRefreshingThread(const LeafMatrix& leaves);
    void end();
 private:
    void refreshScreen();
    void initColoring();
    uint16_t generateColor(uint16_t leafSize);

    LeafMatrix leaves;
    uint16_t width;
    uint16_t height;
    bool work;
};

#endif
