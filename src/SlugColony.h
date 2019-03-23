#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__


#include "Slug.h"

#include <cstdint>
#include <vector>

class Slug;

class SlugColony
{
public:
    SlugColony(uint16_t size);
    void createColony(Coordinates& leafSize);
    const std::vector<Slug>& getColony() const;
    void setColony(std::vector<Slug>& newColony);

private:
    uint16_t size;
    std::vector<Slug> colony;
};

#endif
