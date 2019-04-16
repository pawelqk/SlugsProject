#include "Slug.h"
#include "SlugColony.h"
#include <iostream>
#include <random>

Slug::Slug(Coordinates leafCoords, Coordinates limits):
health(100u), leafCoords(leafCoords), limits(limits), dead(false), ill(false)
{}

uint8_t Slug::getHealth()
{
    return health;
}

const Coordinates& Slug::getLeafCoords() const
{
    return leafCoords;
}

bool Slug::getIll()
{
    return ill;
}

void Slug::setLeaf(const std::shared_ptr<Leaf>& leaf)
{
    currentLeaf = leaf;
}

void Slug::setLeafField(LeafField* leafField)
{
    this->leafField = leafField;
}

Coordinates Slug::moveRandomly()  // TODO: better!!!
{
    // TODO: extract random
    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_int_distribution<std::mt19937::result_type> dist(1, 4);
    auto oldCoords = leafCoords;

    Move move = static_cast<Move>(rand() % 4 + 1);
    if (moveIsPossible(move))
    {
        changePlace(move);
    }

    return oldCoords;
}

std::thread Slug::spawn(const std::shared_ptr<Drawer>& drawer)
{
    this->drawer = drawer;
    return std::thread([this]{ live(); });
}

void Slug::kill()
{
    leafField->getLeaf(leafCoords.first, leafCoords.second)->setTaken(false);
    dead = true;
}

void Slug::live()
{
    while (!dead)
    {
        if (currentLeaf->getSize() != 0)
        {
            currentLeaf->eat();
            if (currentLeaf->getIll() && rand() % 2 == 0)   // TODO: replace random
            {
                ill = true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        else
        {
            movingLock.lock();
            auto oldCoords = moveRandomly();
            currentLeaf = leafField->updatePosition(oldCoords, leafCoords);
            movingLock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        if (ill)
        {
            --health;
        }

        if (health == 0)
        {
            kill();
        }
    }
}

bool Slug::moveIsPossible(Move move)
{
    switch (move)
    {
    case UP:
        return leafCoords.second > 0
           &&  !leafField->getLeaf(leafCoords.first, leafCoords.second - 1)->getTaken();
    case DOWN:
        return leafCoords.second < limits.second - 1
            && !leafField->getLeaf(leafCoords.first, leafCoords.second + 1)->getTaken();
    case LEFT:
        return leafCoords.first > 0
            && !leafField->getLeaf(leafCoords.first - 1, leafCoords.second)->getTaken();
    case RIGHT:
        return leafCoords.first < limits.first - 1
            && !leafField->getLeaf(leafCoords.first + 1, leafCoords.second)->getTaken();
    default:
        // TODO: log here!
        return false;
    }
}

void Slug::changePlace(Move move)
{
    switch (move)
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

