// Тот же самый функционал, только адекватным методом.

#include <ncurses.h>

typedef struct
{
    int x;
    int y;
} coord;

void print_tank(coord head, coord gun, coord ori, int g)
{
    mvaddch(head.y, head.x, '*');

    if (ori.y == 0)    
    {
        mvaddch(head.y + 1, head.x + 1, '*');
        mvaddch(head.y + 1, head.x - 1, '*');
        mvaddch(head.y + 1, head.x + 0, '*');

        mvaddch(head.y - 1, head.x + 1, '*');
        mvaddch(head.y - 1, head.x - 1, '*');
        mvaddch(head.y - 1, head.x + 0, '*');
    }
    else
    {
        mvaddch(head.y + 1, head.x + 1, '*');
        mvaddch(head.y - 1, head.x + 1, '*');
        mvaddch(head.y + 0, head.x + 1, '*');

        mvaddch(head.y + 1, head.x - 1, '*');
        mvaddch(head.y - 1, head.x - 1, '*');
        mvaddch(head.y + 0, head.x - 1, '*');
    }

    mvaddch(head.y + gun.y, head.x + gun.x, g);
}

int main()
{
    initscr(); 
    keypad(stdscr, true); // Служебные кнопки
    noecho(); // Не выводить символы с клавиатуры
    curs_set(0); // Отключить курсор

    int ch;

    coord head = {COLS/2, LINES/2};
    coord gun = {1, 0};
    coord ori = {1, 0};
    int g = '-';

    print_tank(head, gun, ori, g);

    while((ch = getch()) != '0')
    {
        clear();
        switch (ch)
        {
        case KEY_UP:
            head.y -= 1;
            ori.x = 0;
            ori.y = -1;
            break;
        case KEY_DOWN:
            head.y += 1;
            ori.x = 0;
            ori.y = 1;
            break;
        case KEY_RIGHT:
            head.x += 1;
            ori.x = 1;
            ori.y = 0;
            break;
        case KEY_LEFT:
            head.x -= 1;
            ori.x = -1;
            ori.y = 0; 
            break;

        case 'q':
            gun.x = -1;
            gun.y = -1;
            g = '\\';
            break;
        case 'w':
            gun.x = 0;
            gun.y = -1;
            g = '|';
            break;
        case 'e':
            gun.x = 1;
            gun.y = -1;
            g = '/';
            break;
        case 'a':
            gun.x = -1;
            gun.y = 0;
            g = '-';
            break;
        case 'd':
            gun.x = 1;
            gun.y = 0;
            g = '-';
            break;
        case 'z':
            gun.x = -1;
            gun.y = 1;
            g = '/';
            break;
        case 'x':
            gun.x = 0;
            gun.y = 1;
            g = '|';
            break;
        case 'c':
            gun.x = 1;
            gun.y = 1;
            g = '\\';
            break;
        }
        print_tank(head, gun, ori, g);
        refresh();
    }

    endwin(); 
}