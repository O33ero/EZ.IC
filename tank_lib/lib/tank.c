#include <ncurses.h>
#include "tank.h"

void print_tank(Tank tank)
{
    // ГОЛОВА //
    print_char_position(tank.head, '*');

    // ГУСЕНИЦЫ //
    if (tank.forward_vector.y == 0)
    {
        // * Левый край (правый)* //
        mvaddch(tank.head.y - 1, tank.head.x + 0, '#');
        mvaddch(tank.head.y - 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x - 1, '#');

        // * Правый край (левый)* //
        mvaddch(tank.head.y + 1, tank.head.x + 0, '#');
        mvaddch(tank.head.y + 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x - 1, '#');
    }

    if (tank.forward_vector.x == 0)
    {
        // * Левый край (правый)* //
        mvaddch(tank.head.y + 0, tank.head.x - 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x - 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x - 1, '#');

        // * Правый край (левый)* //
        mvaddch(tank.head.y + 0, tank.head.x + 1, '#');
        mvaddch(tank.head.y + 1, tank.head.x + 1, '#');
        mvaddch(tank.head.y - 1, tank.head.x + 1, '#');
    }

    // БАШНЯ //
    switch (tank.guns_direction)
    {
    case FORWARD_LEFT:
        mvaddch(tank.head.y - 1, tank.head.x - 1, '\\');
        break;
    case FORWARD:
        mvaddch(tank.head.y - 1, tank.head.x + 0, '|');
        break;
    case FORWARD_RIGHT:
        mvaddch(tank.head.y - 1, tank.head.x + 1, '/');
        break;
    case LEFT:
        mvaddch(tank.head.y + 0, tank.head.x - 1, '-');
        break;
    case RIGHT:
        mvaddch(tank.head.y + 0, tank.head.x + 1, '-');
        break;
    case BACK_LEFT:
        mvaddch(tank.head.y + 1, tank.head.x - 1, '/');
        break;
    case BACK:
        mvaddch(tank.head.y + 1, tank.head.x + 0, '|');
        break;
    case BACK_RIGHT:
        mvaddch(tank.head.y + 1, tank.head.x + 1, '\\');
        break;
    }
}

void move_tank(Tank *tank, int64_t delta_y, int64_t delta_x, struct Field *arena)
{
    // TODO: придумать способ с меньшим количеством проверок        (ОПТИМИЗАЦИЯ)
    // TODO: разобратся с границами поля, придумать как задать свое (УСЛОЖНЕНИЕ)
    if ( 
    ((tank->head.y + delta_y) != 1 )                && // Верхняя граница
    ((tank->head.y + delta_y) != arena->height - 2) && // Нижняя граница
    ((tank->head.x + delta_x) != 1)                 && // Левая граница
    ((tank->head.x + delta_x) != arena->width - 2)     // Правая граница
    )
    {
        tank->head.y = tank->head.y + delta_y;
        tank->head.x = tank->head.x + delta_x; 
    }
}

Tank new_tank(int64_t head_position_y, int64_t head_position_x, int64_t forward_vector_y, int64_t forward_vector_x, enum Gun guns_direction)
{
    // TODO: в будующем, если будет переписыватся код, нужно обдумать новый механизм конструктора. Хотелось бы, чтоб конструктор возвращал ссылку на объект.
    Tank tank;
    tank.head.y = head_position_y;
    tank.head.x = head_position_x;

    tank.forward_vector.y = forward_vector_y;
    tank.forward_vector.x = forward_vector_x;

    tank.guns_direction = guns_direction;

    return tank;
}