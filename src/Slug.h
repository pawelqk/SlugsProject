#ifndef __SLUG_H__
#define __SLUG_H__

#include "Drawer.h"

#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>

using Coordinates = std::pair<uint16_t, uint16_t>;

static std::mutex lock;

class Slug
{
public:
    static int a;
    enum Move: uint8_t
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    };

    Slug(Coordinates leafCoords, Coordinates limits);
    uint8_t getHealth();
    const Coordinates& getLeafCoords() const;
    Coordinates moveRandomly();
    std::thread spawn(std::shared_ptr<Drawer>& drawer);
private:
    void live();

    uint8_t health;
    Coordinates leafCoords;
    Coordinates limits;
    bool dead;

    std::shared_ptr<Drawer> drawer;
};

#endif
