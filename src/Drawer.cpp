#include "Drawer.h"

#include <stdexcept>
#include <thread>

namespace
{
    const uint16_t HEALTHY_GREEN = 41;
    const uint16_t WEAK_GREEN = 44;
    const uint16_t ILL_LEAF = 13;
    const uint16_t colorPair = 1;
}

Drawer::Drawer(uint16_t width, uint16_t height): width(width), height(height)
{
    initscr();
    if (has_colors() == FALSE)
    {
        throw std::runtime_error("Your terminal doesn't support colors. This program will not start");
    }
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

void Drawer::drawColony(const std::vector<Coordinates>& slugPositions)
{
    for (auto& position : slugPositions)
    {
        move(position.second, position.first);  // TODO: Check why this is inverted
        printw("x");
    }
}

void Drawer::updatePosition(const Coordinates& oldCoords, const Coordinates& newCoords)
{
    move(oldCoords.second, oldCoords.first);
    printw(" ");
    move(newCoords.second, newCoords.first);
    printw("x");
    curs_set(0);
    refresh();
}

void Drawer::updateLeaf(const Coordinates& leafPosition, uint8_t leafSize)    // TODO: this method looks bizarre
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

std::thread Drawer::spawnRefreshingThread(const LeafMatrix& leaves)
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
                auto color = generateColor(5);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(color));

                // if (leaves[i][j]->getIll())
                // {
                //    attroff(COLOR_PAIR(1));
                //    attron(COLOR_PAIR(4));
                // }
                // else if (leaves[i][j]->getSize() == 0)
                // {
                //     attroff(COLOR_PAIR(1));
                //     attron(COLOR_PAIR(3));
                // }
                // else if (leaves[i][j]->getSize() < 30)
                // {
                //     attroff(COLOR_PAIR(1));
                //     attron(COLOR_PAIR(2));
                // }

                if (leaves[i][j]->getTaken())
                {
                    printw("x");
                }
                else
                {
                    printw(" ");
                }

                // attroff(COLOR_PAIR(2));
                // attroff(COLOR_PAIR(3));
                attroff(COLOR_PAIR(color));
                attron(COLOR_PAIR(1));
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
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, ILL_LEAF);
    init_pair(5, COLOR_RED, HEALTHY_GREEN);
    init_pair(6, COLOR_RED, WEAK_GREEN);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_RED, ILL_LEAF);
    attron(COLOR_PAIR(1));
}

uint16_t Drawer::generateColor(uint16_t leafSize)
{
    return 2;
}
