// * СТРУКТУРЫ И ФУНКЦИИ ДЛЯ ТАНКА * //

#ifndef TANK_H
#define TANK_H

#include "advcurses.h"

// Положение пушки
enum Gun            
{
    FORWARD_LEFT,   // * 1 // Впереди левее
    FORWARD,        // * 2 // Впереди
    FORWARD_RIGHT,  // * 3 // Впереди правее                       
    LEFT,           // * 4 // Слева                                // ^ 123 //
    RIGHT,          // * 5 // Справа                               // ^ 4*5 //  
    BACK_LEFT,      // * 6 // Сзади левее (относительно переда)    // ^ 678 //
    BACK,           // * 7 // Сзади                                
    BACK_RIGHT      // * 8 // Сзади правее (относительно переда)
};

// Структура танка
typedef struct 
{
    Position head;

    Position forward_vector;

    enum Gun guns_direction;

} Tank;

// Отрисовка танка
void print_tank(Tank tank);

// Движение танка
void move_tank(Tank *tank, int64_t delta_y, int64_t delta_x, struct Field *arena);

// Конструктор для танка
/* 
* Не лучший вариант, потому что танк тупо копируется,
* а хотелось бы, чтобы возвращалась ссылка на новый объект,
* но тогда нужно переписывать половину кода.
*/
Tank new_tank( int64_t head_position_y, int64_t head_position_x,
               int64_t forward_vector_y, int64_t forward_vector_x,
               enum Gun guns_direction);


#endif