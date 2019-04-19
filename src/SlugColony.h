#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__

#include "Slug.h"

#include <cstdint>
#include <map>
#include <vector>

class Slug;

using Coordinates = std::pair<uint16_t, uint16_t>;

class SlugColony
{
 public:
    SlugColony(uint16_t size, const Coordinates& leafSize);
    virtual ~SlugColony() = default;

    std::map<Coordinates, Slug>& getColony();

    virtual bool checkSlugIllness(Coordinates leafCoords);
    void end();

 private:
    void createColony(const Coordinates& leafSize);

    uint16_t size;
    std::map<Coordinates, Slug> colony;
};

#endif
