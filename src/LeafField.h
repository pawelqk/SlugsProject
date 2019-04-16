#ifndef __LEAF_FIELD_H__
#define __LEAF_FIELD_H__

#include "Leaf.h"
#include "SlugColony.h"

#include <memory>
#include <thread>
#include <vector>

class SlugColony;

using Coordinates = std::pair<uint16_t, uint16_t>;
using LeafMatrix = std::vector<std::vector<std::shared_ptr<Leaf>>>;
using LeafPtr = std::shared_ptr<Leaf>;
using SlugColonyPtr = std::shared_ptr<SlugColony>;

class LeafField
{
 public:
    LeafField(const Coordinates& leafSize, const SlugColonyPtr& colony);

    const LeafMatrix& getLeaves() const;
    const LeafPtr& getLeaf(uint16_t x, uint16_t y) const;

    LeafPtr& updatePosition(const Coordinates& oldCoords, const Coordinates& newCoords);
    std::thread spawnRebuildingThread();

    void end();

 private:
    void rebuild();

    LeafMatrix leaves;
    bool work;
};

#endif
