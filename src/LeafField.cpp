#include "LeafField.h"
#include <iostream>

LeafField::LeafField(std::pair<uint16_t, uint16_t>& sizes)
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

void LeafField::updatePosition(Coordinates& oldCoords, Coordinates& newCoords)
{
    leaves[oldCoords.first][oldCoords.second]->setTaken(false);
    leaves[newCoords.first][newCoords.second]->setTaken(true);
}