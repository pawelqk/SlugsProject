#ifndef __SLUG_H__
#define __SLUG_H__

#include <cstdint>
#include <memory>


using Coordinates = std::pair<uint16_t, uint16_t>;

class Slug
{
public:
    enum Move: uint8_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Slug();
    Slug(Coordinates leafCoords);
    uint8_t getHealth();
    const Coordinates& getLeafCoords() const;
    Coordinates& moveRandomly(Coordinates& limits);

private:
    uint8_t health;
    Coordinates leafCoords;
};

#endif
