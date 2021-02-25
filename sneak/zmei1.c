#include <ncurses.h>
#include <stdio.h>

int main(void)
{
	initscr();
	uint32_t ch;
	

	struct xboct // Структура не должна быть в main
	{
		int x;
		int y;
		int digit; // кто digit, почему у хвоста есть поле digit? что там хранится? 
	};

	struct xboct mass[4];

	char oper = '0';
	int count = 0;
	
	int y = LINES/2;
	int x = COLS/2; 
	int help;

	mass[0].x = COLS/2;
	mass[0].y = LINES/2;
	
	mass[0].digit = 0;
	mass[1].digit = 3;
	mass[2].digit = 2;
	mass[3].digit = 1;

	keypad(stdscr,TRUE);
	curs_set(0);
	mvaddch(LINES/2,COLS/2,'*');
	while((ch = getch()) != 'q')
	{ // T^T ну используйте switch case, пожалуйста. Но это же очень медленно и очень сложно. Ну укуси меня пчела, ну ничего же непонятно.
		if((ch == KEY_UP && oper == 'd') || (ch == KEY_DOWN && oper == 'u') || (ch == KEY_RIGHT && oper == 'l') || (ch == KEY_LEFT && oper == 'r')) //Dvizhenie nazad
		{
			for(int i = 0; i < 4;i++)//Iscli4enie nepravilnoi situation
			{
				for (int j = 0; j < 4 ;j++) // Еще и цикл в цикле, ну можно же проще.
				{
					if(mass[i].digit == 3 && mass[j].digit == 2)
					{
						if(ch == KEY_UP && mass[i].y - 1 == mass[j].y)
						{
							count++;
							break;
						}
						if(ch == KEY_DOWN && mass[i].y + 1 == mass[j].y)
						{
							count++;
							break;
						}
						if(ch == KEY_RIGHT && mass[i].x + 1 == mass[j].x)
						{
							count++;
							break;
						}
						if(ch == KEY_LEFT && mass[i].x - 1 == mass[j].x)
						{
							count++;
							break;
						}
					}
				}
			}

			if (count != 0)
			{
				count = 0;
				continue;
			}
// ebaniy translit
			for(int i = 0; i < 4;i++)//povorot zmei,kogda golova stanovitca hvostom i naoborot
			{
				for(int j = 0;j < 4;j++)// dve {
				{
					if(mass[i].digit == 3 && mass[j].digit == 0 && i != j)
					{
						
						x = mass[i].x;
						y = mass[i].y;
						
						help =	mass[i].x;
						mass[i].x = mass[j].x;
						mass[j].x = help;

						help =	mass[i].y;
						mass[i].y = mass[j].y;
						mass[j].y = help;

					}
					if(mass[i].digit == 2 && mass[j].digit == 1 && i != j)
					{
						
						
						help =	mass[i].x;
						mass[i].x = mass[j].x;
						mass[j].x = help;

						help =	mass[i].y;
						mass[i].y = mass[j].y;
						mass[j].y = help;
					}
				}							
			}
	
		}
// ebaniy translit
		if(ch == KEY_UP) //dvizhenie golovi
			{
			y--;
			mvaddch(y,x,'*');
			oper = 'u';
			}
	
	
		if(ch == KEY_DOWN)
			{
			y++;
			mvaddch(y,x,'*');
			oper = 'd';
			}

		if(ch == KEY_LEFT)
			{
				x--;
				mvaddch(y,x,'*');
				oper = 'l';
			}
	
		if(ch == KEY_RIGHT)
			{
				x++;
				mvaddch(y,x,'*');
				oper = 'r';
			}
// ne ydobno chitat' eto huety. Nahyi ya pishy pravila esli ih nikto ne chitaet
		for(int i = 0; i < 4;i++)//dobavlenie k kajdoi 4asti zmei god zhizni 
			{
					mass[i].digit++;
					if(mass[i].digit == 4)// pri 4 godah XBOCT otmiraet
					{
						if(x != mass[i].x || y != mass[i].y)//Yslovie kogda golova ne  vstaet na mesto XBOCTa
						mvaddch(mass[i].y,mass[i].x,' ');

						mass[i].x = x;//otrashivanie golovi
						mass[i].y = y;
						mass[i].digit = 0;
					}
			}
	


	}
	refresh();
	endwin();

	return 0;
}
