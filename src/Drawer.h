#ifndef __DRAWER_H__
#define __DRAWER_H__

#include "Slug.h"
#include "SlugColony.h"

#include <cstdint>
#include <curses.h>
#include <utility>


class Drawer
{
public:
    Drawer(uint16_t width, uint16_t height);
    void drawLeaf();
    void drawColony(SlugColony& colony);
    void updatePosition(Slug slug, Coordinates oldPosition);
private:
    uint16_t width;
    uint16_t height;
};

#endif