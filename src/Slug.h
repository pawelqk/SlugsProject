#ifndef __SLUG_H__
#define __SLUG_H__

#include "Drawer.h"
#include "Leaf.h"

#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>

using Coordinates = std::pair<uint16_t, uint16_t>;

static std::mutex movingLock;
static std::mutex leafLock;

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

    Slug() = default;
    Slug(Coordinates leafCoords, Coordinates limits);
    uint8_t getHealth();
    const Coordinates& getLeafCoords() const;

    void setLeaf(const std::shared_ptr<Leaf>& leaf);
    void setLeafField(const std::shared_ptr<LeafField>& leafField);

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
    std::shared_ptr<LeafField> leafField;
};

#endif
