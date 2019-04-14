#include "LeafField.h"
#include <iostream>

namespace
{
    constexpr uint16_t REBUILD_PERIOD = 3000;
}


LeafField::LeafField(const std::pair<uint16_t, uint16_t>& sizes): work(true)
{
    leaves.resize(sizes.first);
    for (auto& row : leaves)
    {
        row = std::vector<LeafPtr>(sizes.second);
        for (auto& leaf : row)
        {
            leaf = std::make_shared<Leaf>();
        }
    }
}

const LeafMatrix& LeafField::getLeaves() const
{
    return leaves;
}

const LeafPtr& LeafField::getLeaf(uint16_t x, uint16_t y) const
{
    return leaves[x][y];
}

LeafPtr& LeafField::updatePosition(const Coordinates& oldCoords, const Coordinates& newCoords)
{
    leaves[oldCoords.first][oldCoords.second]->setTaken(false);
    leaves[newCoords.first][newCoords.second]->setTaken(true);
    return leaves[newCoords.first][newCoords.second];
}

std::thread LeafField::spawnRebuildingThread()
{
    return std::thread([this](){ rebuild(); });
}

void LeafField::rebuild()
{
    while (work)
    {
        for (auto& row : leaves)
        {
            for (auto& leaf : row)
            {
                if (leaf->getSize() < 100 && !leaf->getTaken())
                {
                    leaf->regenerate();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(REBUILD_PERIOD));
    }
}

void LeafField::end()
{
    work = false;
}

