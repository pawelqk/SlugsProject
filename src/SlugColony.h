#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__

#include "Slug.h"

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>

#include "ConcurrencyDispatcher.h"

class Slug;

using Coordinates = std::pair<uint16_t, uint16_t>;

class SlugColony
{
 public:
    SlugColony(uint16_t size, const Coordinates& leafSize);
    void createColony(const Coordinates& leafSize);

    std::map<Coordinates, Slug>& getColony();

    bool checkSlugIllness(Coordinates leafCoords);
    void start(const std::shared_ptr<ConcurrencyDispatcher>& dispatcher,
        const std::vector<std::function<std::thread()>>& threadSpawners);

    void end();

    void killSlug(const Coordinates& slugCoords);
    void createNewSlug(const Slug& slug);
    
    static std::mutex mutex;   
 private:
    uint16_t size;
    std::map<Coordinates, Slug> colony;

    std::shared_ptr<ConcurrencyDispatcher> dispatcher;
};

#endif
