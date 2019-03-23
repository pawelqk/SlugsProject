#include "Slug.h"

#include <iostream>
#include <random>

Slug::Slug()
{
    std::cout << "Slug con" << std::endl;
}

Slug::Slug(Coordinates leafCoords): leafCoords(leafCoords)
{}

uint8_t Slug::getHealth()
{
    return health;
}

const Coordinates& Slug::getLeafCoords() const
{
    return leafCoords;
}

Coordinates Slug::moveRandomly(Coordinates& limits) // TODO: better!!!
{
    // TODO: extract
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 4);
    auto oldCoords = leafCoords;
    // TODO: they're not going left. Debugging move with (x,y) is required
    switch(static_cast<Move>(dist(rng)))
    {
    case UP:
        if (leafCoords.second > 0)
        {
            leafCoords.second--;
        }
        break;
    case DOWN:
        if (leafCoords.second < limits.second - 1)
        {
            leafCoords.second++;
        }
        break;
    case LEFT:
        if (leafCoords.first > 0)
        {
            leafCoords.first--;
        }
        break;
    case RIGHT:
        if (leafCoords.first < limits.first - 1)
        {
            leafCoords.first++;
        }
        break;
    }

    return oldCoords;
}

