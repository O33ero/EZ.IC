#include <ncurses.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>


typedef struct  // Позиция или Вектор
{
    int64_t y;
    int64_t x;
} Position;

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

struct Field // Игровое поле
{
    uint32_t height;
    uint32_t width;
};

struct Bullet
{
    Position position;
    Position vector;
    bool is_dead;
};

void print_char_position(Position p, char ch)
{
    mvaddch(p.y, p.x, ch);
}

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

    // БАШНАЯ //
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

struct Bullet init_bullet(Tank* tank)
{
    struct Bullet b;
    b.is_dead = 1;
    b.position.x = tank->head.x;
    b.position.y = tank->head.y;

    switch (tank->guns_direction)
    {
    case FORWARD_LEFT:
        b.vector.x = -1;
        b.vector.y = -1;
        break;
    case FORWARD:
        b.vector.x = 0;
        b.vector.y = -1;
        break;
    case FORWARD_RIGHT:
        b.vector.x = 1;
        b.vector.y = -1;
        break;
    case LEFT:
        b.vector.x = -1;
        b.vector.y = 0;
        break;
    case RIGHT:
        b.vector.x = 1;
        b.vector.y = 0;
        break;
    case BACK_LEFT:
        b.vector.x = -1;
        b.vector.y = 1;
        break;
    case BACK:
        b.vector.x = 0;
        b.vector.y = 1;
        break;
    case BACK_RIGHT:
        b.vector.x = 1;
        b.vector.y = 1;
        break;
    }
    b.position.x += (b.vector.x * 2);
    b.position.y += (b.vector.y * 2);

    return b;
}

void print_bullet(struct Bullet b)
{
    if (!b.is_dead)
        print_char_position(b.position, '+');
}

void move_bullet(struct Bullet* b, struct Field* arena)
{
    if (!b->is_dead)
    {
        b->position.x += b->vector.x * 2;
        b->position.y += b->vector.y * 2;

        if ( 
        (b->position.y  == 1 )                && // Верхняя граница
        (b->position.y == arena->height - 2) && // Нижняя граница
        (b->position.x == 1)                 && // Левая граница
        (b->position.x == arena->width - 2)     // Правая граница
        )
        {
            b->is_dead = 1; 
        }
    }
    
}

int main()
{
    char str_hello[] = "Want play my game?";
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

    // --- Танк игрока ---//
    Tank player;
    player.head.y = LINES / 2;
    player.head.x = COLS / 2;

    player.forward_vector.y = 0;
    player.forward_vector.x = 1;
    
    player.guns_direction = FORWARD;
    // --- Снаряд ---//
    struct Bullet b;
    b = init_bullet(&player);

    // * Игровое поле * //
    struct Field arena = {LINES, COLS};

    // * Привет! * // 
    mvaddstr(LINES / 2, COLS / 2 - 10, str_hello);
    mvaddstr(LINES - 2, COLS / 2 - 8, str_continue);
    box(stdscr, 0, 0);

    refresh();
    //getch();

    // * Первая отрисовка * //
    clear();
    box(stdscr, 0, 0);
    color_set(2, NULL);
    print_tank(player);
    color_set(1, NULL);
    refresh();

    halfdelay(1);

// * Главный игровой цикл * //
    while (!exit)
    {
        clock_t t = clock(); // Начало фрейма
        flushinp(); // Отчистка потока ввода
        ch = getch();
        t = clock() - t; // Конец фрейма https://sprosi.pro/questions/43939/zmeya-s-ncurses-v-c

        double sec_elapsed = ((double)t)/CLOCKS_PER_SEC; // Секунд
        int ms_elapsed = (int)(sec_elapsed*1000000); // Микросекунд
        if (ch != ERR)  usleep(100000 - ms_elapsed);

        clear(); // Отрисовка фрейма

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

        case ' ':
            b = init_bullet(&player);
            b.is_dead = 0;
            break;

        case 'p': // Выход
            exit = 1;
            break;
        }

        box(stdscr, 0, 0);
        color_set(2, NULL);
        print_tank(player);
        color_set(1, NULL);

        move_bullet(&b, &arena);
        print_bullet(b);
        refresh();
    }



    endwin();

    return 0;
}