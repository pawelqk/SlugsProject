#include "Slug.h"

#include <iostream>

Slug::Slug()
{
    std::cout << "Slug con" << std::endl;
}

Slug::Slug(std::pair<uint16_t, uint16_t> leafCoords): leafCoords(leafCoords)
{}

uint8_t Slug::getHealth()
{
    return health;
}

const std::pair<uint16_t, uint16_t>& Slug::getLeafCoords() const
{
    return leafCoords;
}



