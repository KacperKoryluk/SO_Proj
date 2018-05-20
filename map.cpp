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
	dontAvoidThis.x = 2;
	dontAvoidThis.y = 10;
	while(true){
		move(dontAvoidThis.x, dontAvoidThis.y);
		for(int i=0; i<3; i++)
		printw("O");
		refresh();
		usleep(sec/2);
		move(dontAvoidThis.x, dontAvoidThis.y);
		printw("   ");
		dontAvoidThis = moveBadObject(dontAvoidThis);
		refresh();
		if(dontAvoidThis.y ==37)
			dontAvoidThis.y = 10;
	}
}
//Thr func with bigger obstacle
void badObjectBehaviour2() {
	BadObject dontAvoidThis;
	dontAvoidThis.x = 3;
	dontAvoidThis.y = 10;
	while(true){
		move(dontAvoidThis.x, dontAvoidThis.y);
		for(int i=0; i<5; i++)
		printw("O");
		refresh();
		usleep(sec/4);
		move(dontAvoidThis.x, dontAvoidThis.y);
		printw("     ");
		dontAvoidThis = moveBadObject(dontAvoidThis);
		refresh();
		if(dontAvoidThis.y ==36)
			dontAvoidThis.y = 10;
	}
}
//Border render
void printMap()
{
	printw("          ");
	for(int i=0; i<30; i++)
	printw("-");
	printw("\n");
	for(int i=0; i<20; i++)
	{	
		for(int j=0; j<9; j++)
			printw(" ");
		printw("|");
		for(int j=0; j<30; j++)
			printw(" ");
		printw("|");
		printw("\n");
		
	}\
	printw("          ");
	for(int i=0; i<30; i++)
		printw("-");
}
int main()
{

	std::thread thr[5];
	std::thread thr2[2];

	initscr();
	noecho();
	cbreak();
	curs_set(0);
	printMap();
	for (int i = 0; i < 5; i++)
	{
		thr[i] = std::thread(badObjectBehaviour);
		if(i<2)
		{
			thr2[i] = std::thread(badObjectBehaviour2);
		}
	 	usleep(3*sec);

	}
	for (int i = 0; i <1; i++)
	{
		thr[i].join();
		thr2[i].join();
	}


	getch();
	endwin();
	return 0;
}
