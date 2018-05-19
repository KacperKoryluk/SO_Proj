#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>

struct Frog {
	int x;
	int y;	
};

void moveFrog(Frog frog)
{	
	
	move(frog.x, frog.y);
	printw("M");
	refresh();
}

Frog frogLeft(Frog frog)
{
	frog.x--;
	return frog;
}

Frog frogRight(Frog frog)
{
	frog.x++;
	return frog;
}

Frog frogForward(Frog frog)
{
	frog.y = frog.y+1;
	return frog;
}

Frog frogBackwards(Frog frog)
{
	frog.y--;
	return frog;
}

void *frogAround(void *arg) {
Frog frog;
frog.x = 10;
frog.y = 10;

moveFrog(frog);

while (true) {

	int ch = getch();
	move(frog.x, frog.y);
	printw(" ");
	if (ch == 'd') {
		frog = frogForward(frog);
	}
	
	if (ch == 'w') {
		frog = frogLeft(frog);
	}
	
	if (ch == 's') {
		frog = frogRight(frog);
	}	
	if (ch == 'a'){
		frog = frogBackwards(frog);
	}
		moveFrog(frog);
		refresh();
	}
}



int main()
{
	pthread_t thr;
	int rc;

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	rc = pthread_create(&thr, NULL, &frogAround, NULL);

	pthread_join(thr, NULL);

	getch();
	//while(true);
	endwin();
	return 0;

}
