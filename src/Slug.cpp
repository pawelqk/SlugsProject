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

void Slug::moveRandomly(Drawer& drawer) // TODO: better!!!
{
    // TODO: extract
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 4);

}

