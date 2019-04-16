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
    explicit LeafField(const Coordinates& sizes);

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
