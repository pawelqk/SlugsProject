#include "Leaf.h"

#include <iostream>

Leaf::Leaf(): Leaf(100u)
{}

Leaf::Leaf(uint8_t size): size(size), taken(false), ill(false)
{}

uint8_t Leaf::getSize()
{
    return size;
}

bool Leaf::getTaken()
{
    return taken;
}

bool Leaf::getIll()
{
    return ill;
}

void Leaf::setTaken(bool taken)
{
    this->taken = taken;
}

void Leaf::regenerate()
{
    if (size++ == 0)
    {
        if (rand() % 5 == 0) // TODO: replace with real random engine
        {
           ill = true;
        }
        else if (ill)
        {
            ill = false;
        }
    }
}

void Leaf::eat()
{
    --size;
}
