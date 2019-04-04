#include "Drawer.h"

#include <stdexcept>
#include <thread>

namespace
{
    const uint16_t HEALTHY_GREEN = 41;
    const uint16_t WEAK_GREEN = 44;
    const uint16_t colorPair = 1;
}

Drawer::Drawer(uint16_t width, uint16_t height): width(width), height(height)
{
    initscr();
    if (has_colors() == FALSE)
    {
        throw std::runtime_error("Your terminal doesn't support colors. This program will not start");
    }
    // logger(DEBUG) << "Creating drawer with width: " << width << " and height: " << height << std::endl;
    initColoring();
}

Drawer::~Drawer()
{
    attroff(COLOR_PAIR(colorPair));
    endwin();
}

void Drawer::drawLeaf()
{
    attron(COLOR_PAIR(1));
    for (auto i = 0u; i < height; ++i)
    {
        mvhline(i, 0, ' ', width);
    }
}

void Drawer::drawColony(std::vector<Coordinates>& slugPositions)
{
    for (auto& position : slugPositions)
    {
        move(position.second, position.first); // TODO: Check why this is inverted
        printw("x");
    }
}

void Drawer::updatePosition(Coordinates& oldCoords, Coordinates& newCoords)
{
    move(oldCoords.second, oldCoords.first);
    printw(" ");
    move(newCoords.second, newCoords.first);
    printw("x");
    curs_set(0);
    refresh();
}

void Drawer::updateLeaf(Coordinates& leafPosition, uint8_t leafSize)    // TODO: this method looks bizarre
{
    // uint16_t currentColor = colorPair;
    // uint16_t leafColor = getColorBasedOnLeafSize(leafSize);
    // attroff(COLOR_PAIR(currentColor));
    // attron(COLOR_PAIR(leafColor));
    // move(leafPosition.second, leafPosition.first);
    // printw("x");
    // curs_set(0);
    // refresh();
    // attroff(COLOR_PAIR(leafColor));
    // attron(COLOR_PAIR(currentColor));
}

std::thread Drawer::spawnRefreshingThread(LeafMatrix& leaves)
{
    this->leaves = leaves;
    return std::thread([this](){ refreshScreen(); });
}

void Drawer::refreshScreen()
{
    while (true)
    {
        for (auto i = 0u; i < width; i++)
        {
            for (auto j = 0u; j < height; j++)
            {
                move(j, i);
                // logger(DEBUG) << __FUNCTION__ << "Checking height: " << i << " width: " << j << std::endl;

                if (leaves[i][j]->getTaken())
                {
                    // logger(DEBUG) << "Found taken leaf at width " << i << " height: " << j << std::endl;
                    printw("x");
                }
                else
                {
                    printw(" ");
                }
            }
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Drawer::initColoring()
{
    start_color();
    init_pair(1, COLOR_BLACK, HEALTHY_GREEN);
    init_pair(2, COLOR_BLACK, WEAK_GREEN);
    attron(COLOR_PAIR(1));
}

uint16_t Drawer::getColorBasedOnLeafSize(uint16_t leafSize)
{
    return 2;
}