#include "SlugColony.h" 
#include <algorithm>
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
        Slug slug(slugCoords, leafSize, this);
        colony[slugCoords] = slug;
    }
}

std::map<Coordinates, Slug>& SlugColony::getColony()
{
    return colony;
}

bool SlugColony::checkSlugIllness(Coordinates leafCoords)
{
    auto it = std::find_if(colony.begin(), colony.end(),
        [&leafCoords](auto slug){ return slug.second.getLeafCoords() == leafCoords; });

    return (it != colony.end()) && it->second.getIll();
}

void SlugColony::start(const std::shared_ptr<ConcurrencyDispatcher>& dispatcher,
    const std::vector<std::function<std::thread()>>& threadSpawners)
{
    this->dispatcher = dispatcher;
    dispatcher->beginExecuting(threadSpawners);
}

void SlugColony::end()
{
    for (auto& slug : colony)
    {
        slug.second.kill();
    }
}

void SlugColony::killSlug(const Coordinates& slugCoords)
{
    auto it = std::find_if(colony.begin(), colony.end(),
        [&slugCoords](auto slug){ return slug.second.getLeafCoords() == slugCoords; });

    if (it == colony.end())
    {
        return;
    }

    it->second.kill();
    colony.erase(it);
}

void SlugColony::createNewSlug(const Slug& slug)
{
    colony[slug.getLeafCoords()] = slug;
    dispatcher->createNew(colony[slug.getLeafCoords()].receiveSpawner(),
        colony[slug.getLeafCoords()].receiveKiller());
}
