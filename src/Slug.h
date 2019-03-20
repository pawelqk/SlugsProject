#include "Leaf.h"

#include <cstdint>
#include <memory>

class Slug
{
public:
    Slug();
    Slug(std::pair<uint16_t, uint16_t> leafCoords);
    uint8_t getHealth();
    const std::pair<uint16_t, uint16_t>& getLeafCoords() const;

private:
    uint8_t health;
    std::pair<uint16_t, uint16_t> leafCoords;
};

