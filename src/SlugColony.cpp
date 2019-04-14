#include "SlugColony.h"

#include <iostream>
#include <random>
#include <set>

SlugColony::SlugColony(uint16_t size): size(size)
{}

void SlugColony::createColony(const Coordinates& leafSize)
{
    leafField = std::make_shared<LeafField>(leafSize);
    // TODO: mb extract random instance
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> distX(0, leafSize.first - 1);
    // std::uniform_int_distribution<std::mt19937::result_type> distY(0, leafSize.second - 1);
    std::set<uint16_t> takenX;
    std::set<uint16_t> takenY;

    for (auto i = 0u; i < size; ++i)
    {
        uint16_t x;
        uint16_t y;
        do
        {
            // x = distX(rng);
            // y = distY(rng);
            x = rand() % leafSize.first;
            y = rand() % leafSize.second;
        } while (takenX.find(x) != takenX.end() || takenY.find(y) != takenY.end());

        auto slugCoords = std::make_pair(x, y);
        Slug slug(slugCoords, leafSize);
        auto leaf = leafField->getLeaf(x, y);
        leaf->setTaken(true);
        slug.setLeaf(leaf);
        slug.setLeafField(leafField);
        colony[slugCoords] = slug;
    }
}

std::map<Coordinates, Slug>& SlugColony::getColony()
{
    return colony;
}

const std::shared_ptr<LeafField>& SlugColony::getLeafField() const
{
    return leafField;
}


void SlugColony::end()
{
    for (auto& slug : colony)
    {
        slug.second.kill();
    }
}