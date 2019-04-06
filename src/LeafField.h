#ifndef __LEAF_FIELD_H__
#define __LEAF_FIELD_H__

#include "Leaf.h"

#include <memory>
#include <thread>
#include <vector>

using Coordinates = std::pair<uint16_t, uint16_t>;
using LeafMatrix = std::vector<std::vector<std::shared_ptr<Leaf>>>;
using LeafPtr = std::shared_ptr<Leaf>;

class LeafField
{
public:
    LeafField(std::pair<uint16_t, uint16_t>& sizes);

    const LeafMatrix& getLeaves() const;
    const LeafPtr& getLeaf(uint16_t x, uint16_t y) const;

    LeafPtr& updatePosition(Coordinates& oldCoords, Coordinates& newCoords);
    std::thread spawnRebuildingThread();

private:
    void rebuild();

    LeafMatrix leaves;
};

#endif
