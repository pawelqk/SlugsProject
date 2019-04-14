#ifndef __SLUG_COLONY_H__
#define __SLUG_COLONY_H__

#include "LeafField.h"
#include "Slug.h"

#include <cstdint>
#include <map>
#include <vector>


class SlugColony
{
 public:
    explicit SlugColony(uint16_t size);
    void createColony(const Coordinates& leafSize);

    std::map<Coordinates, Slug>& getColony();
    const std::shared_ptr<LeafField>& getLeafField() const;

    void end();

 private:
    uint16_t size;
    std::map<Coordinates, Slug> colony;
    std::shared_ptr<LeafField> leafField;
};

#endif
