#include <ncurses.h>
#include "advcurses.h"

void print_char_position(Position p, char ch)
{
    mvaddch(p.y, p.x, ch);
}