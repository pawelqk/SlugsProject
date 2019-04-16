#include "SlugColony.h"

#include <iostream>
#include <random>
#include <set>

SlugColony::SlugColony(uint16_t size, const Coordinates& leafSize): size(size)
{
    createColony(leafSize);
}

void SlugColony::createColony(const Coordinates& leafSize)
{
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
        colony[slugCoords] = slug;
    }
}

std::map<Coordinates, Slug>& SlugColony::getColony()
{
    return colony;
}

bool SlugColony::checkSlugIllness(Coordinates leafCoords)
{
    return colony.find(leafCoords) == colony.end() || colony[leafCoords].getIll();
}

void SlugColony::end()
{
    for (auto& slug : colony)
    {
        slug.second.kill();
    }
}
