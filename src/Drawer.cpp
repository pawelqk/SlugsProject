#include "Drawer.h"

#include <stdexcept>
#include <thread>

namespace
{
    constexpr uint16_t HEALTHY_GREEN = 41;
    constexpr uint16_t WEAK_GREEN = 44;
    constexpr uint16_t ILL_LEAF = 13;
    constexpr uint16_t colorPair = 1;
}

Drawer::Drawer(uint16_t width, uint16_t height, const std::shared_ptr<SlugColony>& colony):
    width(width), height(height), colony(colony), work(true)
{
    initscr();
    noecho();
    if (has_colors() == FALSE)
    {
        throw std::runtime_error(
            "Your terminal doesn't support colors. This program will not start");
    }
    initColoring();
}

Drawer::~Drawer()
{
    attroff(COLOR_PAIR(colorPair));
    endwin();
}

void Drawer::setLeaves(const LeafMatrix& leaves)
{
    this->leaves = leaves;
}

std::thread Drawer::spawnRefreshingThread()
{
    return std::thread([this](){ refreshScreen(); });
}

void Drawer::end()
{
    work = false;
    attroff(COLOR_PAIR(1));
    refresh();
    endwin();
}

void Drawer::refreshScreen()
{
    while (work)
    {
        for (auto i = 0u; i < width; i++)
        {
            for (auto j = 0u; j < height; j++)
            {
                move(j, i);
                uint8_t color = generateColor(leaves[i][j]);

                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(color));

                if (colony->checkSlugIllness({i, j}))
                {
                    color += 4;
                }

                attron(COLOR_PAIR(color));
                if (leaves[i][j]->getTaken())
                {
                    printw("x");
                }
                else if (leaves[i][j]->getEgg())
                {
                    printw("0");
                }
                else
                {
                    printw(" ");
                }

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
    init_pair(1, COLOR_YELLOW, HEALTHY_GREEN);
    init_pair(2, COLOR_YELLOW, WEAK_GREEN);
    init_pair(3, COLOR_YELLOW, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, ILL_LEAF);
    init_pair(5, COLOR_BLACK, HEALTHY_GREEN);
    init_pair(6, COLOR_BLACK, WEAK_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, ILL_LEAF);
    init_pair(9, COLOR_RED, HEALTHY_GREEN);
    init_pair(10, COLOR_RED, WEAK_GREEN);
    init_pair(11, COLOR_RED, COLOR_WHITE);
    init_pair(12, COLOR_RED, ILL_LEAF);
    attron(COLOR_PAIR(1));
}

uint16_t Drawer::generateColor(const std::shared_ptr<Leaf>& leaf)
{
    uint16_t color;
    if (leaf->getIll())
    {
        color = 4;
    }
    else if (leaf->getSize() == 0)
    {
        color = 3;
    }
    else if (leaf->getSize() < 30)
    {
        color = 2;
    }
    else
    {
        color = 1;
    }

    return color + 4;
}
