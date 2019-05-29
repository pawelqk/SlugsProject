#include "Slug.h"
#include "SlugColony.h"
#include <iostream>
#include <random>

Slug::Slug(Coordinates leafCoords, Coordinates limits, SlugColony* colony):
health(100u), leafCoords(leafCoords), limits(limits), colony(colony), dead(false), ill(false)
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
    if (!currentLeaf)
    {
        throw std::exception();
    }
}

void Slug::setDrawer(const std::shared_ptr<Drawer>& drawer)
{
    this->drawer = drawer;
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
        leafCoords = changePlace(move, leafCoords);
    }

    return oldCoords;
}

std::thread Slug::spawn()
{
    return std::thread([this]{ live(); });
}

std::function<std::thread()> Slug::receiveSpawner()
{
    return [this](){ return spawn(); };
}


void Slug::kill()
{
    currentLeaf->setTaken(false);
    dead = true;
}

std::function<void()> Slug::receiveKiller()
{
    return [this](){ kill(); };
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
            if (currentLeaf->getEgg() && (rand() % 5 == 0))
            {
                Move moveToNeighbour = tryToMoveFreeLeaf();
                if (moveToNeighbour != NONE)
                {
                    createSlug(moveToNeighbour);
                }
                currentLeaf->setEgg(false);
            }
            else if (!(currentLeaf->getEgg()) && (rand() % 5 == 0))
            {
                currentLeaf->setEgg(true);
            }

            movingLock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        if (ill)
        {
            if (--health == 0)
            {
                kill();
            }
            else
            {
                Move moveToNeighbour = tryToMoveToReachSlug();
                if (moveToNeighbour == NONE)
                {
                    movingLock.lock();
                    auto oldCoords = moveRandomly();
                    currentLeaf = leafField->updatePosition(oldCoords, leafCoords);
                    currentLeaf->setEgg(false);
                    movingLock.unlock();
                }
                else
                {
                    movingLock.lock();
                    eatSlug(moveToNeighbour);
                    movingLock.unlock();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
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

Coordinates Slug::changePlace(Move move, const Coordinates& currentCoords)
{
    auto leafCoords = currentCoords;
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
    default:
        break;
    }

    return leafCoords;
}

Slug::Move Slug::tryToMoveToReachSlug()
{
    for (auto& moveToLeaf : getMovesToNeighbourLeaves())
    {
        if (moveToLeaf.second->getTaken())
        {
            return moveToLeaf.first;
        }
    }

    return NONE;
}

Slug::Move Slug::tryToMoveFreeLeaf()
{
    for (auto& moveToLeaf : getMovesToNeighbourLeaves())
    {
        if (!moveToLeaf.second->getTaken())
        {
            return moveToLeaf.first;
        }
    }

    return NONE;
}

std::map<Slug::Move, std::shared_ptr<Leaf>> Slug::getMovesToNeighbourLeaves()
{
    std::map<Move, std::shared_ptr<Leaf>> movesToNeighbours;
    
    if (leafCoords.second > 0)
    {
        movesToNeighbours[UP] = leafField->getLeaf(
                leafCoords.first, leafCoords.second - 1);
    }
    if (leafCoords.second < limits.second - 1)
    {
        movesToNeighbours[DOWN] = leafField->getLeaf(
                leafCoords.first, leafCoords.second + 1);
    }
    
    if (leafCoords.first > 0)
    {
        movesToNeighbours[LEFT] = leafField->getLeaf(
                leafCoords.first - 1, leafCoords.second);
    }
    if (leafCoords.first < limits.first - 1)
    {
        movesToNeighbours[RIGHT] = leafField->getLeaf(
                leafCoords.first + 1, leafCoords.second);
    }
    
    return movesToNeighbours;
}

void Slug::eatSlug(Move moveToNeighbour)
{   
    auto newCoords = changePlace(moveToNeighbour, leafCoords);
    colony->killSlug(newCoords);
    currentLeaf = leafField->updatePosition(leafCoords, newCoords);
    leafCoords = newCoords;
}

void Slug::createSlug(Move moveToNeighbour)
{
    auto newCoords = changePlace(moveToNeighbour, leafCoords);
    const auto& newSlugsLeaf = leafField->getLeaf(newCoords.first, newCoords.second);
    Slug newSlug(newCoords, limits, colony);
    newSlug.setLeaf(newSlugsLeaf);
    newSlug.setLeafField(leafField);
    newSlugsLeaf->setTaken(true);

    colony->createNewSlug(newSlug);
}

