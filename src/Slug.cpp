#include "Slug.h"

#include <iostream>
#include <random>

Slug::Slug(Coordinates leafCoords, Coordinates limits):
leafCoords(leafCoords), limits(limits), dead(false)
{}

uint8_t Slug::getHealth()
{
    return health;
}

const Coordinates& Slug::getLeafCoords() const
{
    return leafCoords;
}

Coordinates Slug::moveRandomly() // TODO: better!!!
{
    // TODO: extract random
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 4);
    auto oldCoords = leafCoords;

    Move move = static_cast<Move>(dist(rng));
    if (moveIsPossible(move))
    {
        changePlace(move);
    }

    return oldCoords;
}

std::thread Slug::spawn(std::shared_ptr<Drawer>& drawer)
{
    this->drawer = drawer;
    return std::thread([=]{ live();});
}

void Slug::kill()
{
    dead = true;
}

void Slug::live()
{
    while (!dead)
    {
        lock.lock();
        auto oldCoords = moveRandomly();
        drawer->updatePosition(oldCoords, leafCoords);
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

bool Slug::moveIsPossible(Move move)
{
    switch(move)
    {
    case UP:
        return leafCoords.second > 0;
    case DOWN:
        return leafCoords.second < limits.second - 1;
    case LEFT:
        return leafCoords.first > 0;
    case RIGHT:
        return leafCoords.first < limits.first - 1;
    default:
        // TODO: log here!
        return false;
    }
}

void Slug::changePlace(Move move)
{
    switch(move)
    {
    case UP:
        leafCoords.second--;
        break;
    case DOWN:
        leafCoords.second++;
        break;
    case LEFT:
        leafCoords.first--;
        break;
    case RIGHT:
        leafCoords.first++;
        break;
    }
}

