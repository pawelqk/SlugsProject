#include "Logger.h"
#include "SlugColony.h"

#include <random>
#include <unordered_set>

SlugColony::SlugColony(uint8_t size): size(size)
{}

void SlugColony::createColony(std::pair<uint16_t, uint16_t>& leafSize)
{
    Logger logger("SlugColony::createColony");
    // TODO: mb extract random instance
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distX(0, leafSize.first - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distY(0, leafSize.second - 1);
    std::unordered_set<uint16_t> takenX;
    std::unordered_set<uint16_t> takenY;

    for (auto i = 0u; i < size; ++i)
    {
        uint16_t x;
        uint16_t y;
        do
        {
            x = distX(rng);
            y = distY(rng);
        } while (takenX.find(x) != takenX.end() || takenY.find(y) != takenY.end());
        // TODO: fix logging
        logger << "emplacing slug no: " + std::to_string(i) + " with coords: " + std::to_string(x) + " " + std::to_string(y);
        colony.emplace_back(std::make_pair(x,y));
    }
}

const std::vector<Slug>& SlugColony::getColony() const
{
    return colony;
}

