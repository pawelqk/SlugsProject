#ifndef __SLUG_H__
#define __SLUG_H__

#include "Drawer.h"
#include "Leaf.h"
#include "SlugColony.h"

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <thread>

class LeafField;
class Drawer;
class SlugColony;

using Coordinates = std::pair<uint16_t, uint16_t>;

class Slug
{
 public:
    enum Move: uint8_t
    {
        NONE = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Slug() = default;
    Slug(Coordinates leafCoords, Coordinates limits, SlugColony* colony);
    uint8_t getHealth();
    const Coordinates& getLeafCoords() const;
    bool getIll();

    void setLeaf(const std::shared_ptr<Leaf>& leaf);
    void setDrawer(const std::shared_ptr<Drawer>& drawer);
    void setLeafField(LeafField* leafField);

    Coordinates moveRandomly();
    std::thread spawn();
    std::function<std::thread()> receiveSpawner();
    void kill();
    std::function<void()> receiveKiller();
 private:
    void live();
    bool moveIsPossible(Move move);
    Coordinates changePlace(Move move, const Coordinates& currentCoords);
    Move tryToMoveToReachSlug();
    Move tryToMoveFreeLeaf();
    std::map<Move, std::shared_ptr<Leaf>> getMovesToNeighbourLeaves();
    void eatSlug(Move moveToNeighbour);
    void createSlug(Move moveToNeighbour);

    uint8_t health;
    Coordinates leafCoords;
    Coordinates limits;
    SlugColony* colony;
    bool dead;
    bool ill;

    std::shared_ptr<Leaf> currentLeaf;
    std::shared_ptr<Drawer> drawer;
    LeafField* leafField;
};

#endif
