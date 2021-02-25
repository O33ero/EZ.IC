// * НАДСТРОЙКА НАД NCURSES * //

#ifndef ADVCURSES_H
#define ADVCURSES_H

#include <stdint.h>

typedef struct  // Позиция или Вектор
{
    int64_t y;
    int64_t x;
} Position;

struct Field // Игровое поле
{
    uint32_t height;
    uint32_t width;
};

void print_char_position(Position p, char ch);

#endif