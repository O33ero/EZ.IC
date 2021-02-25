#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>

struct Position // Позиция
{
    uint64_t y;
    uint64_t x;
};

struct snake_4 // Структура 4-х головой змеи
{
    struct Position head_0;
    struct Position head_1;
    struct Position head_2;
    struct Position head_3;
};

struct Field // Игровое поле
{
    uint32_t height;
    uint32_t width;
};

// Отприсовка поля
void print_field(struct Field arena) 
{
    mvaddch(0, 0, '+');
    mvaddch(arena.height - 1, 0, '+');
    mvaddch(0, arena.width - 1, '+');
    mvaddch(arena.height - 1, arena.width - 1, '+');

    for (int i = 1; i < arena.width - 1; i ++)
    {
        mvaddch(0, i, '-');
        mvaddch(arena.height - 1, i, '-');
    }

    for (int i = 1; i < arena.height - 1; i ++)
    {
        mvaddch(i, 0, '|');
        mvaddch(i, arena.width - 1, '|');
    }
}

// Нарисовать символ по позиции
void print_char_position(struct Position p, char ch)
{
    mvaddch(p.y, p.x, ch);
}

// Нарисовать 4-х головую змею
void print_snake(struct snake_4 snake)
{
    print_char_position(snake.head_0, 'A');
    print_char_position(snake.head_1, 'B');
    print_char_position(snake.head_2, 'C');
    print_char_position(snake.head_3, 'D');
}

// Сместить змею по вектору
void move_snake(struct snake_4 *snake, int64_t delta_y, int64_t delta_x)
{
    snake->head_3.x = snake->head_2.x;
    snake->head_3.y = snake->head_2.y;

    snake->head_2.x = snake->head_1.x;
    snake->head_2.y = snake->head_1.y;

    snake->head_1.x = snake->head_0.x;
    snake->head_1.y = snake->head_0.y;

    snake->head_0.y = snake->head_0.y + delta_y;
    snake->head_0.x = snake->head_0.x + delta_x;
}

// *main* //
int main()
{
    char str_hello[] = "Want play my game?";
    char str_continue[] = "press any key...";
    char str_q[] = "press Q to exit...";
    char str_lose[] = "You DEAD!";

    int ch;

    initscr();
    noecho(); // Не выводить символы
    curs_set(0); // Отключить курсор
    keypad(stdscr, true); // Корректный вывод системных кпопок
    uint8_t exit = 0; // Проверка выхода

    // * Структура игрока * //
    struct snake_4 player;
    player.head_0.y = LINES / 2;
    player.head_0.x = COLS / 2;
    player.head_1.y = LINES / 2;
    player.head_1.x = COLS / 2 - 1;
    player.head_2.y = LINES / 2;
    player.head_2.x = COLS / 2 - 2;
    player.head_3.y = LINES / 2;
    player.head_3.x = COLS / 2 - 3;

    // * Вектор последнего перемещения * // По умолчанию - вправо
    struct Position last_vector;
    last_vector.x = 1;
    last_vector.y = 0;

    // * Структура арены * //
    struct Field arena = {LINES, COLS};


    // ! НАЧАЛО ИГРЫ ! //
    // * Привет! * //
    mvaddstr(LINES / 2, COLS / 2 - 10, str_hello);
    mvaddstr(LINES - 2, COLS / 2 - 8, str_continue);
    print_field(arena);
    refresh();
    getch();
    clear();

    // * Первая отрисовка * //
    print_field(arena);
    print_snake(player);
    refresh();

    halfdelay(2);                                // ! Каждый тик 0.2 секунды
    // * Главный игровой цикл * //
    while (!exit)
    {
        ch = getch();
        clear();

        switch (ch)
        {
        case ERR: // Нет инпутов (или неверный инпут)
            move_snake(&player, last_vector.y, last_vector.x);
            break;
        case KEY_UP: // Вверх
            move_snake(&player, -1, 0); // Смещение зависимо от кнопки
            last_vector.y = -1;
            last_vector.x = 0;
            break;
        case KEY_DOWN: // Вниз
            move_snake(&player, 1, 0);
            last_vector.y = 1;
            last_vector.x = 0;
            break;
        case KEY_RIGHT: // Вправо
            move_snake(&player, 0, 1);
            last_vector.y = 0;
            last_vector.x = 1;
            break;
        case KEY_LEFT: // Влево
            move_snake(&player, 0, -1);
            last_vector.y = 0;
            last_vector.x = -1;
            break;
        case 'q': // Выход
            exit = 1;
            break;
        }
        print_field(arena); // Отрисовка арены
        print_snake(player); // Отрисовка игрока
        refresh();


        if (player.head_0.y == 0 || player.head_0.x == 0) // Вверхняя/правая стена
        { 
            mvaddstr(LINES / 2, COLS / 2 - 5, str_lose);
            mvaddstr(LINES - 2, COLS / 2 - 10, str_q);
            cbreak();
            break;
        }
        if (player.head_0.y == arena.height - 1 || player.head_0.x == arena.width - 1) // Нижняя/левая стена
        { 
            mvaddstr(LINES / 2, COLS / 2 - 5, str_lose);
            mvaddstr(LINES - 2, COLS / 2 - 10, str_q);
            cbreak();
            break;
        }

    }

    while (!exit) // Выход // ! временный костыль
    {
        ch = getch();
        if (ch == 'q')
            exit = 1;
    }

    endwin();
    return 0;
}