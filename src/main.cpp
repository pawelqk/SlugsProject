#include "Leaf.h"

#include <curses.h>

void rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

int main()
{
    initscr();
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    attron(COLOR_PAIR(1));
    for (int y = 0; y < 3; y++) {
        mvhline(y, 0, ' ', 7);
    }
    move(1,3);
    printw("o");
    move(20,20);
    // move(1,4);
    // printw("*");
    // move(2,3);
    // printw("*");
    // move(2,4);
    // printw("*");
    // rectangle(0,0,20,20);
    curs_set(0);
    getch();
    endwin();
}
