#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

int main(int argc, const char** argv)
{
	initscr();
	
	addstr("Hello NCurses\n");
	addstr("Second line\n");
	refresh();

	move(3, 102);
	addch('|');

	for(int i=0;i<=100;i++)
	{
		move(3, i);
		addch('-');
		move(3, i+1);
		addch('>');
		move(4, 0);
		printw("%2d %%", i);
		refresh();
		napms(10);
	}

	move(7, 0);
	addstr("Music player");
	refresh();

	time_t timer;
	srand(&timer);

	int columns = 150;
	for (int s=0; s < 100; s++)
	{
		for (int i=0;i<columns;i++)
		{
			int mh = 20;
			int h = 1 + rand() % mh;
			for (int y=0; y < mh; y++)
			{
				move(30-y, i);
				char c = rand() % 64;
				addch(y<h?c + 33:' ');
			}
			//printw("%d-", rand() % 6);
		}
		refresh();
		napms(100);
	}

	refresh();
	
	sleep(1);

	endwin();
	return 0;
}
