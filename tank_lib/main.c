#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>

#include "lib/tank.h"
#include "lib/advcurses.h"



int main()
{
    char str_hello[] = "Want play my game?"; // ? можно вынести все фразы в отдельный заголовочный с define, чтоб не лежало тут
    char str_continue[] = "press any key...";

    int ch;

    initscr();
    noecho(); // Не выводить символы
    curs_set(0); // Отключить курсор
    keypad(stdscr, true); // Корректный вывод системных кпопок

    // * ЗАГОТОВКИ ЦВЕТОВ * //
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // СТАНДАРТ
    init_pair(2, COLOR_BLUE, COLOR_BLACK);  // СОЮЗНИК
    init_pair(3, COLOR_RED, COLOR_BLACK);   // ПРОТИВНИК
    color_set(1, NULL);
    uint8_t exit = 0; // Проверка выхода

    Tank player = new_tank(LINES/2, COLS/2, 1, 0, FORWARD); //TODO: не лучший вариант, нужен новый 
    
    
    // * Игровое поле * //
    struct Field arena = {LINES, COLS};

    // * Привет! * // 
    mvaddstr(LINES / 2, COLS / 2 - 10, str_hello);
    mvaddstr(LINES - 2, COLS / 2 - 8, str_continue);
    box(stdscr, 0, 0);

    refresh();
    getch();

    // * Первая отрисовка * //
    clear();
    box(stdscr, 0, 0);
    color_set(2, NULL);
    print_tank(player);
    color_set(1, NULL);
    refresh();

// * Главный игровой цикл * //
    while (!exit)
    {
        ch = getch();
        clear();

        switch (ch)
        {
        case KEY_UP: // Вверх
            move_tank(&player, -1, 0, &arena);
            player.forward_vector.y = -1;
            player.forward_vector.x = 0;
            break;
        case KEY_DOWN: // Вниз
            move_tank(&player, 1, 0, &arena);
            player.forward_vector.y = 1;
            player.forward_vector.x = 0;
            break;
        case KEY_RIGHT: // Вправо
            move_tank(&player, 0, 1, &arena);
            player.forward_vector.y = 0;
            player.forward_vector.x = 1;
            break;
        case KEY_LEFT: // Влево
            move_tank(&player, 0, -1, &arena);
            player.forward_vector.y = 0;
            player.forward_vector.x = -1;
            break;

        case 'q':
            player.guns_direction = FORWARD_LEFT;
            break;
        case 'w':
            player.guns_direction = FORWARD;
            break;
        case 'e':
            player.guns_direction = FORWARD_RIGHT;
            break;
        case 'a':
            player.guns_direction = LEFT;
            break;
        case 'd':
            player.guns_direction = RIGHT;
            break;
        case 'z':
            player.guns_direction = BACK_LEFT;
            break;
        case 'x':
            player.guns_direction = BACK;
            break;
        case 'c':
            player.guns_direction = BACK_RIGHT;
            break;

        case 'p': // Выход
            exit = 1;
            break;
        }

        box(stdscr, 0, 0);
        color_set(2, NULL);
        print_tank(player);
        color_set(1, NULL);
        refresh();
    }



    endwin();

    return 0;
}