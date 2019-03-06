#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

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
		napms(100);
	}

	sleep(1);

	endwin();
	return 0;
}
