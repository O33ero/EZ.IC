#include <ncurses.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

struct Position // * Позиция
{
    uint64_t y;
    uint64_t x;
};

struct snake // * Структура 4-х головой змеи
{
    struct Position* head;
    size_t size;
};

struct Field // * Игровое поле
{
    uint32_t height;
    uint32_t width;
};

struct Apple
{
    struct Position place;
    bool is_dead;
};

// * Отприсовка поля
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

// * Нарисовать символ по позиции
void print_char_position(struct Position p, char ch)
{
    mvaddch(p.y, p.x, ch);
}

// * Нарисовать 4-х головую змею
void print_snake(struct snake snake)
{
    for (int i = 0; i < snake.size; i++)
        print_char_position(snake.head[i], 'A' + i);
}

// * Сместить змею по вектору
void move_snake(struct snake *snake, int64_t delta_y, int64_t delta_x)
{
    for (int i = (snake->size) - 1; i >= 1; i--)
    {
        snake->head[i].x = snake->head[i - 1].x;
        snake->head[i].y = snake->head[i - 1].y;
    }

    snake->head[0].y = snake->head[0].y + delta_y;
    snake->head[0].x = snake->head[0].x + delta_x;
}

// * Отрисовка яблочка
void print_apple(struct Apple apple)
{
    if (!apple.is_dead)
        print_char_position(apple.place, 'o');
}

// * Генерация рандомной позиции
void random_coord(struct Position *p, struct Field arena)
{
    srand(time(NULL));

    p->x = rand() % (arena.width - 2) + 1;
    p->y = rand() % (arena.height - 2) + 1;
}

// * Генерирует массив координат заданной длины 
struct Position* generate_coord_array(size_t size)
{
    struct Position* p;
    p = (struct Position*) malloc(sizeof(struct Position) * size);

    return p;
}

// * Увеличение массива координат
struct Position* regenerate_coord_array(struct Position* p, size_t new_size)
{
    p = (struct Position*)realloc(p, new_size * sizeof(struct Position));
    return p;
}

// --- main --- //
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

    // --- Структура игрока --- //
    struct snake player;
    player.size = 4;
    player.head = generate_coord_array(player.size);
    player.head[0].y = LINES / 2;
    player.head[0].x = COLS / 2;
    player.head[1].y = LINES / 2;
    player.head[1].x = COLS / 2 - 1;
    player.head[2].y = LINES / 2;
    player.head[2].x = COLS / 2 - 2;
    player.head[3].y = LINES / 2;
    player.head[3].x = COLS / 2 - 3;

    // --- Вектор последнего перемещения --- // По умолчанию - вправо
    struct Position last_vector;
    last_vector.x = 1;
    last_vector.y = 0;

    // --- Структура арены --- //
    struct Field arena = {LINES, COLS};

    // --- Яблочки --- //
    struct Apple apple;
    apple.is_dead = 0;
    apple.place.x = 0;
    apple.place.y = 0;
    random_coord(&(apple.place), arena);



    // ! НАЧАЛО ИГРЫ ! //
    // --- Привет! --- //
    mvaddstr(LINES / 2, COLS / 2 - 10, str_hello);
    mvaddstr(LINES - 2, COLS / 2 - 8, str_continue);
    print_field(arena);
    refresh();
    getch();
    clear();

    // --- Первая отрисовка --- //
    print_field(arena);
    print_snake(player);
    refresh();

    halfdelay(2);                                // ! Каждый тик 0.2 секунды
    // --- Главный игровой цикл --- //
    while (!exit)
    {
        clock_t t = clock(); // Начало фрейма
        flushinp(); // Отчистка потока ввода
        ch = getch();
        t = clock() - t; // Конец фрейма https://sprosi.pro/questions/43939/zmeya-s-ncurses-v-c

        double sec_elapsed = ((double)t)/CLOCKS_PER_SEC; // Секунд
        int ms_elapsed = (int)(sec_elapsed*1000000); // Микросекунд
        //if (ch != ERR)  usleep(200000 - ms_elapsed);

        clear(); // Отрисовка фрейма

        switch (ch)
        {
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
        default: // Нет инпутов (или неверный инпут)
            move_snake(&player, last_vector.y, last_vector.x);
            break;
        }


        //--- Яблочко съедено ---//
        if (player.head[0].x == apple.place.x && player.head[0].y == apple.place.y)
        {
            random_coord(&(apple.place), arena);
            player.size += 1;
            player.head = regenerate_coord_array(player.head, player.size);
        }




        //--- Отрисовка ---//
        print_field(arena); // Отрисовка арены
        print_snake(player); // Отрисовка игрока
        print_apple(apple);
        refresh();

        //--- Смэрть ---//
        if (player.head[0].y == 0 || player.head[0].x == 0) // Вверхняя/правая стена
        { 
            mvaddstr(LINES / 2, COLS / 2 - 5, str_lose);
            mvaddstr(LINES - 2, COLS / 2 - 10, str_q);
            cbreak();
            exit = 1;
        }
        if (player.head[0].y == arena.height - 1 || player.head[0].x == arena.width - 1) // Нижняя/левая стена
        { 
            mvaddstr(LINES / 2, COLS / 2 - 5, str_lose);
            mvaddstr(LINES - 2, COLS / 2 - 10, str_q);
            cbreak();
            exit = 1;
        }
        for (int i = 3; i < player.size; i++)
        {
            if (player.head[0].x == player.head[i].x && player.head[0].y == player.head[i].y)
            {
                mvaddstr(LINES / 2, COLS / 2 - 5, str_lose);
                mvaddstr(LINES - 2, COLS / 2 - 10, str_q);
                cbreak();
                exit = 1;
                break;
            }
        }

        

    }

    while (exit != 2) // Выход // ! временный костыль, но нет ничего более постоянного, чем временное
    {
        ch = getch();
        if (ch == 'q')
            exit = 2;
    }

    endwin();
    return 0;
}