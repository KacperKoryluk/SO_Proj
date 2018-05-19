#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <thread>

#define sec 1000000

struct BadObject {
	int x;
	int y;
	int i;
};

struct GoodObject {
	int x;
	int y;
	int i;
};

BadObject moveBadObject (BadObject badObject) {
	badObject.y++;
	return badObject;
}
//Thr func
void badObjectBehaviour() {
	BadObject dontAvoidThis;
	dontAvoidThis.x = 0;
	dontAvoidThis.y = 10;
	

	while(dontAvoidThis.x < 40){
		move(dontAvoidThis.x, dontAvoidThis.y);
		printw("OOO");
		refresh();
		usleep(sec/2);
		move(dontAvoidThis.x, dontAvoidThis.y);
		printw("   ");
		dontAvoidThis = moveBadObject(dontAvoidThis);
		refresh();
	}


}	

int main()
{

	std::thread thr[5];
	
	
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	for (int i = 0; i < 5; i++)
	{
		thr[i] = std::thread(badObjectBehaviour);
		usleep(3*sec);

	}
	for (int i = 0; i <1; i++)
	{
		thr[i].join();
	}


	getch();
	endwin();
	return 0;
}
