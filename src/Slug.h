#ifndef __SLUG_H__
#define __SLUG_H__

#include "Drawer.h"
#include "Leaf.h"

#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>

using Coordinates = std::pair<uint16_t, uint16_t>;

static std::mutex lock;

class Slug
{
public:
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

    void setLeaf(std::shared_ptr<Leaf>& leaf);

    Coordinates moveRandomly();
    std::thread spawn(std::shared_ptr<Drawer>& drawer);
    void kill();
private:
    void live();
    bool moveIsPossible(Move move);
    void changePlace(Move move);

    uint8_t health;
    Coordinates leafCoords;
    Coordinates limits;
    bool dead;

    std::shared_ptr<Leaf> currentLeaf;
    std::shared_ptr<Drawer> drawer;
};

#endif
