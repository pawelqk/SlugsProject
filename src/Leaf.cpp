#include "Leaf.h"

#include <iostream>

Leaf::Leaf(): Leaf(100u)
{}

Leaf::Leaf(uint8_t size): size(size), taken(false)
{}

uint8_t Leaf::getSize()
{
    return size;
}

bool Leaf::getTaken()
{
    return taken;
}

void Leaf::setTaken(bool taken)
{
    this->taken = taken;
}

void Leaf::regenerate()
{
    ++size;
}

void Leaf:: eat()
{
    --size;
}