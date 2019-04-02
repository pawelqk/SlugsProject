#include "LeafField.h"


LeafField::LeafField(std::pair<uint16_t, uint16_t>& sizes)
{
    leaves.resize(sizes.first);
    for (auto& row : leaves)
    {
        row = std::vector<LeafPtr>(sizes.second, std::make_shared<Leaf>());
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
    leaves[oldCoords.second][oldCoords.first]->setTaken(false);
    leaves[newCoords.second][newCoords.first]->setTaken(true);
}