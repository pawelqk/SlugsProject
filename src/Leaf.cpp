#include "Leaf.h"

#include <iostream>

Leaf::Leaf(): Leaf(100u)
{}

Leaf::Leaf(uint8_t size): size(size), taken(false), ill(false), egg(false)
{}

uint8_t Leaf::getSize()
{
    return size;
}

bool Leaf::getTaken()
{
    return taken.load();
}

bool Leaf::getIll()
{
    return ill.load();
}

bool Leaf::getEgg()
{
    return egg.load();
}

void Leaf::setTaken(bool taken)
{
    this->taken.store(taken);
}

void Leaf::setEgg(bool egg)
{
    this->egg.store(egg);
}

void Leaf::regenerate()
{
    if (size++ == 0)
    {
        if (ill)
        {
            ill.store(false);
        }
        else if (rand() % 5 == 0)  // TODO: replace with real random engine
        {
            ill.store(true);
        }

    }
}

void Leaf::eat()
{
    --size;
}
