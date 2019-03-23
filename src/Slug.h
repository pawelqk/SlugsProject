#ifndef __SLUG_H__
#define __SLUG_H__

#include "Drawer.h"

#include <cstdint>
#include <memory>

class Drawer;

class Slug
{
public:
    enum Move: uint8_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Slug();
    Slug(Coordinates leafCoords);
    uint8_t getHealth();
    const Coordinates& getLeafCoords() const;
    void moveRandomly(Drawer& drawer);

private:
    uint8_t health;
    Coordinates leafCoords;
};

#endif
