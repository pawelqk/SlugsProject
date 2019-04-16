#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "LeafField.h"

#include <cstdint>
#include <curses.h>
#include <memory>
#include <utility>
#include <vector>
#include <thread>

class SlugColony;

using Coordinates = std::pair<uint16_t, uint16_t>;
using LeafMatrix = std::vector<std::vector<std::shared_ptr<Leaf>>>;

class Drawer
{
 public:
    Drawer(uint16_t width, uint16_t height, const std::shared_ptr<SlugColony>& colony);
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
    std::shared_ptr<SlugColony> colony;
    bool work;
};

#endif
