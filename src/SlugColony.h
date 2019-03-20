#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__

#include "Leaf.h"
#include "Slug.h"

#include <cstdint>
#include <vector>

class SlugColony
{
public:
    SlugColony(uint8_t size);
    void createColony(std::pair<uint16_t, uint16_t>& leafSizs);
    const std::vector<Slug>& getColony() const;

private:
    uint8_t size;
    std::vector<Slug> colony;
};

#endif
