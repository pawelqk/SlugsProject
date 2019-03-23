#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__

#include "Drawer.h"

#include <cstdint>
#include <vector>

class Slug;

class SlugColony
{
public:
    SlugColony(uint16_t size);
    void createColony(Coordinates& leafSizs);
    const std::vector<Slug>& getColony() const;

private:
    uint16_t size;
    std::vector<Slug> colony;
};

#endif
