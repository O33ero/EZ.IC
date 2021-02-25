#include <ncurses.h>

// *Вертикальное положение танка* //
void v_tank(int x, int y, int key)
{
    mvaddch(y, x, '*'); // Отрисовка головы

    mvaddch(y + 1, x + 1, '*'); // Отрисовка правого шасси
    mvaddch(y + 0, x + 1, '*');
    mvaddch(y - 1, x + 1, '*');

    mvaddch(y + 1, x - 1, '*');// Отрисовка левого шасси
    mvaddch(y + 0, x - 1, '*');
    mvaddch(y - 1, x - 1, '*');

    if (key == KEY_UP) // Фишка от автора. Хочу чтобы танк на затылке имел доп. защиту  в виде лишней *
        mvaddch(y + 1, x + 0, '*');
    else
        mvaddch(y - 1, x + 0, '*');
}

// *Горизонтальное положение танка* //
void h_tank(int x, int y, int key)
{
    mvaddch(y, x, '*'); // Отрисовка головы

    mvaddch(y + 1, x + 1, '*'); // Отрисовка левого шасси
    mvaddch(y + 1, x + 0, '*');
    mvaddch(y + 1, x - 1, '*');

    mvaddch(y - 1, x + 1, '*');// Отрисовка правого шасси
    mvaddch(y - 1, x + 0, '*');
    mvaddch(y - 1, x - 1, '*');

    if (key == KEY_LEFT) // Фишка от автора. Хочу чтобы танк на затылке имел доп. защиту в виде лишний *
        mvaddch(y + 0, x + 1, '*');
    else
        mvaddch(y + 0, x - 1, '*');
}

// *Отрисовка пушки, в зависимости от направления* //
void cannon(int head_x, int head_y, int v_x, int v_y, char cannon)
{
    mvaddch(head_y + v_y, head_x + v_x, cannon);
}

// *Отрисовка танка и пушки, в зависимости от последнего направления* //
void print_tank(int ch_memory_move, int head_x, int head_y, int v_x, int v_y, char ch_memory_cannon)
{
    if (ch_memory_move == KEY_UP || ch_memory_move == KEY_DOWN) // Если последние движение вверх или вниз, то танк будет вертикальным
        v_tank(head_x, head_y, ch_memory_move);
    else // Иначе, соответсвенно, горизонтально
        h_tank(head_x, head_y, ch_memory_move);

    cannon(head_x, head_y, v_x, v_y, ch_memory_cannon);
}

int main()
{
	int i_chto_dalshe = 0;

	char cannon_UP_DOWN = '|'; // указатели на конст-чар????
    char cannon_LEFT_RIGHT = '-';
    char cannon_C_RIGHT_LEFT = '/';
    char cannon_C_LEFT_RIGHT = '\\';

	int ch;

    initscr(); 
    keypad(stdscr, true); // Служебные кнопки
    noecho(); // Не выводить символы с клавиатуры
    curs_set(0); // Отключить курсор

    int ch_memory_move = KEY_RIGHT; // Оставлю эту переменную, но можно обойтись и без неё.

    int x = 5; // Нулевая позиция танка
	int y = 5;
    int ch_memory_cannon = cannon_LEFT_RIGHT; // Нулевое положение пушки (вправо)

    int v_x, v_y; // Куда пушка смотрит?
    v_x = 1; // Это по иксу влево  // * В сумме
    v_y = 0; // И по игреку никуда // * Вперед = вправо -> пушка вправо



    mvaddch(y, x, '*'); // Отрисовка головы (башни)
    
    // Будем считать, что стандарнтое положение, когда танк смотрит влево. Пушка, соответственно, тоже влево.
    mvaddch(y + 1, x + 1, '*'); // Отрисовка левого шасси
    mvaddch(y + 1, x + 0, '*');
    mvaddch(y + 1, x - 1, '*');

    mvaddch(y - 1, x + 1, '*');// Отрисовка правого шасси
    mvaddch(y - 1, x + 0, '*');
    mvaddch(y - 1, x - 1, '*');

    mvaddch(y + 0, x - 1, '*');
    // Отрисовывается явно тут. Все повторные отрисовки вызываются через функцию h_tank или v_tank.

    mvaddch(y + v_y, x + v_x, cannon_LEFT_RIGHT); // Не забываем про пушку, она все же самая главная деталь танка
    refresh(); // Выгружаем из памяти



   	while((ch = getch()) != '0'){
        clear(); // Вынесем затирание экрана ведь неважно какую кнопку нажмут, все равно будет затираение. Так зачем размазывать код.

    	if(ch == KEY_UP){ // Если нажата стрелочка вверх, то двигаем голову и обрисовываем вокруг неё весь танк
            y = y - 1;
            x = x + 0;

            ch_memory_move = KEY_UP; // Ну и сохраним последние направление, мало ли кто нибудь решит их украсть.

            v_tank(x, y, ch_memory_move); // Очевидно, если танк едет вверх, то и рисуем его вертикально.
            cannon(x, y, v_x, v_y, ch_memory_cannon); // А пушка не поворачивает. А можно сделать так, чтобы поворачивала, но это опционало опционально и легко делается.ьно и легко делается.
    	}
    	
        if(ch == KEY_DOWN){ // Если нажата стрелочка вниз, то двигаем голову вниз и обрисовываем вокруг неё танк
            y = y + 1;
            x = x + 0;
            
            ch_memory_move = KEY_DOWN;

            v_tank(x, y, ch_memory_move);
            cannon(x, y, v_x, v_y, ch_memory_cannon); 
    	}
    	
        if(ch == KEY_LEFT){
            y = y + 0;
            x = x - 1;
            
            ch_memory_move = KEY_LEFT; 

            h_tank(x, y, ch_memory_move);
            cannon(x, y, v_x, v_y, ch_memory_cannon);
    	}
    	
        if(ch == KEY_RIGHT){
            y = y + 0;
            x = x + 1;
            
            ch_memory_move = KEY_RIGHT;

            h_tank(x, y, ch_memory_move);
            cannon(x, y, v_x, v_y, ch_memory_cannon); 
    	}

        switch (ch) // А еще в си существует конструкция, которая позволяет осуществлять проверка возможных значений без if. Эта конструкция называется swtich case. Это элементарная конструкция, которая проходится на первом занятии по Си.
        {
        case 'q': // Если пушку повернули на q, то теперь пушка меняется на C_LEFT_RIGHT, а вектор пушки меняется на (x, y) = (-1,-1)
            v_x = -1;
            v_y = -1;
            ch_memory_cannon = cannon_C_LEFT_RIGHT; // Перезаписываем состояние пушки
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon); // Можно обойтись и без этого, но уже загнались в такие рамки, поэтому придется повторить её 8 раз. Тут уже ничего не поделать.
            break;
        case 'w':
            v_x = 0;
            v_y = -1;
            ch_memory_cannon = cannon_UP_DOWN;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'e':
            v_x = 1;
            v_y = -1;
            ch_memory_cannon = cannon_C_RIGHT_LEFT;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'a':
            v_x = -1;
            v_y = 0;
            ch_memory_cannon = cannon_LEFT_RIGHT;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'd':
            v_x = 1;
            v_y = 0;
            ch_memory_cannon = cannon_LEFT_RIGHT;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'z':
            v_x = -1;
            v_y = 1;
            ch_memory_cannon = cannon_C_RIGHT_LEFT;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'x':
            v_x = 0;
            v_y = 1;
            ch_memory_cannon = cannon_UP_DOWN;
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        case 'c':
            v_x = 1;
            v_y = 1;
            ch_memory_cannon = cannon_C_LEFT_RIGHT; 
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
            break;
        default: // Если нажата неправильная кнопка, то просто перерисуем танк, чтобы ничего не сломалось
            print_tank(ch_memory_move, x, y, v_x, v_y, ch_memory_cannon);
        }

        refresh(); // Такая же логика для refresh, как и для clear.

    }      

    /*
    * Еще можно сделать, чтобы пушка следовала за поворотом танка. 
    * Дабы все вектора у нас есть, сделать это не сложно.
    * Но это занятие на час-полтора (может меньше, если повезет).
    */
    getch();                     
    endwin();                   
    return 0;
}