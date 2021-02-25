//exit=='k'
// Пиздец, это выше моих сил. Переписывать 500 строк кода нереально. Просто вот вопрос. Тебе же к этому надо будет писать стрельбу, 
// коллизию с другими танками, сетевой код. Просто предположи как ты к ЭТОМУ будешь дописывать, что то сверху.
#include <ncurses.h>
#include <unistd.h>

int main (void)
{	
	int ch,cl;
	int x,y,x1,x2,y1,y2,x3,y3,x4,y4,x5,x6,x7,y5,y6,y7;
	x=3;
	y=3;
	x1=2;
	y1=2;
	x2=4;
	y2=2;
	x3=2;
	y3=3;
	x4=4;
	y4=3;
	x5=2;
	y5=4;
	x6=4;
	y6=4;
	x7=3;
	y7=4;
	cl=0;
	initscr();
	mvaddch(y,x,'*');
	mvaddch(y1,x1,'*');
	mvaddch(y2,x2,'*');
	mvaddch(y3,x3,'*');
	mvaddch(y4,x4,'*');
	mvaddch(y5,x5,'*');
	mvaddch(y6,x6,'*');
	mvaddch(y7,x7,'|');
	refresh();
	keypad(stdscr,TRUE);
	while ((ch=getch())!='k')
		
		{
		
					
		if (ch==KEY_DOWN && cl <3) 
					{ 
					y7=y+1;
					x7=x;
					y1=y3;
					y3=y5;
					y2=y4;
					y4=y6;
			  		x=x;
			  		y=y+1;
			  		if (y7<=y)
			  		y7=y+1;
			  		y5=y5+1;
			  		y6=y6+1;
			  		
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
			  		refresh();
			
					}	
			
				
		 
		 if (ch==KEY_UP && cl < 3) 
			{ 		x7=x;
					y7=y-1;
					y5=y3;
					y3=y1;
			  		y6=y4;
			  		y4=y2;
			  		x=x;
			  		y=y-1;
			  		if (y7>=y)
			  		y7=y-1;
			  		y1=y1-1;
			  		y2=y2-1;
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
					
			  		refresh();
			 
			
			}
			
			if (ch==KEY_UP && cl >2)
			{ 		
					y7=y-1;
					x7=x;
					x2=x2+2;
					x4=x4+1;
					y4=y4+1;
					y6=y6+2;
			  		y1=y1-2;
			  		x3=x3-1;
			  		y3=y3-1;
			  		x5=x5-2;
			  		if (y7>=y)
			  		y7=y-1;
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
			  		refresh();
			 		cl=1;
			}
			
			
		 if (ch==KEY_DOWN && cl >2)
			{ 		
					y7=y+1;
					x7=x;
					x2=x2+2;
					x4=x4+1;
					y4=y4+1;
					y6=y6+2;
			  		y1=y1-2;
			  		x3=x3-1;
			  		y3=y3-1;
			  		x5=x5-2;
			  		if (y7<=y)
			  		y7=y+1;
			  		
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
			  		refresh();
			 		cl=1;
			}
			
			
		 
		 
		 
		 
		 
		 if (ch==KEY_RIGHT && cl < 3)
			{ 		
					x7=x+2;
					y7=y;
					x2=x2-2;
					x4=x4-1;
					y4=y4-1;
					y6=y6-2;
			  		y1=y1+2;
			  		x3=x3+1;
			  		y3=y3+1;
			  		x5=x5+2;
			  		if (x7<=x)
			  		x7=x7+3;
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
			  		refresh();
			 		cl=4;
			}
		 if (ch==KEY_LEFT && cl < 3)
			{ 		
					y7=y;
					x7=x-1;
					x2=x2-2;
					x4=x4-1;
					y4=y4-1;
					y6=y6-2;
			  		y1=y1+2;
			  		x3=x3+1;
			  		y3=y3+1;
			  		x5=x5+2;
			  		
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
			  		refresh();
			 		cl=3;
			}
		 
		 
		 if (ch==KEY_LEFT && cl>2)
			{ 		
					y7=y;
					x7=x-1;
					x6=x4;
					x4=x2;
			  		x2=x2-1;
			  		x=x-1;
			  		x5=x3;
			  		x3=x1;
			  		x1=x1-1;
			  		if (x7>=x)
			  		x7=x7-1;
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
			  		refresh();
			 
			}

 		if (ch==KEY_RIGHT && cl>2) 
			{ 		
					x7=x+1;
					y7=y;
					x2=x4;
					y2=y4;
					x4=x6;
					y4=y6;
					x6=x6+1;
					x=x+1;
					y=y;
					x1=x3;
					y1=y3;
					x3=x5;
					y3=y5;
					x5=x5+1;
					if (x7<=x)
					x7=x7+1;
			  		clear();
			  		
	                               mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
			  		refresh();
			 	
			}
		if (cl<3)
		{ if (ch == 'q' || ch == 'Q' ) 
			{ 		clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'\\');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					refresh();
		       } 
		if (ch == 'W' || ch == 'w' ) 
			{ 		
					if (y7>y)
					y7=y7-2;
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
					refresh();
		       } 
		if (ch == 'e' || ch == 'E' ) 
			{ 		clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'/');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y6,x6,'*');
					refresh();
			}
		
		if (ch == 'd' || ch == 'D' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'-');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					
					refresh();
		       } 
		if (ch == 'c' || ch == 'C' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'\\');
					
					refresh();
		       } 
		if (ch == 'x' || ch == 'X' ) 
			{ 		
					if (y7<y)
					y7=y7+2;
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'|');
					refresh();
		       } 
		
		if (ch == 'z' || ch == 'Z' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'/');
					mvaddch(y6,x6,'*');
					
					refresh();
			}
		
		
		if (ch == 'a' || ch == 'A' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'-');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					refresh();
			}
		};
		if (cl>2)
		{ if (ch == 'q' || ch == 'Q' ) 
			{ 		clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'\\');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					refresh();
		       } 
		if (ch == 'W' || ch == 'w' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'|');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					
					refresh();
		       } 
		if (ch == 'e' || ch == 'E' ) 
			{ 		clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'/');
					
					refresh();
			}
		
		if (ch == 'd' || ch == 'D' ) 
			{ 		
					if(x7<x)
					x7=x7+2;
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
					
					refresh();
		       } 
		if (ch == 'c' || ch == 'C' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'\\');
					mvaddch(y6,x6,'*');
					
					refresh();
		       } 
		if (ch == 'x' || ch == 'X' ) 
			{ 		
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'|');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					refresh();
		       } 
		
		if (ch == 'z' || ch == 'Z' ) 
			{ 		
					
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'/');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					
					refresh();
			}
		
		
		if (ch == 'a' || ch == 'A' ) 
			{ 		
					if (x7>x)
					x7=x7-2;
					clear();
					mvaddch(y,x,'*');
					mvaddch(y1,x1,'*');
					mvaddch(y2,x2,'*');
					mvaddch(y3,x3,'*');
					mvaddch(y4,x4,'*');
					mvaddch(y5,x5,'*');
					mvaddch(y6,x6,'*');
					mvaddch(y7,x7,'-');
					
					refresh();
			}
		};
		
		
		
		
		};
	endwin();
	return 0;
}
