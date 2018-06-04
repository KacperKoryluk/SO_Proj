#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <thread>
#include <ctime>

#define sec 1000000
bool moveObstacles = true;
bool frogLifetime = true;
int points = 0;
std::thread frogThread;
std::thread flyThreads[4];


struct Frog {
	int x;
	int y;	
};
struct Fly {
	int x;
	int y;
};
Fly fly;
void sitFly(Fly fly)
{
	move(fly.x, fly.y);
	printw("K");
	refresh();
}
Frog frog; //Frog here
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

void Death()
{   
    move(frog.x, frog.y);
    printw("X");
    move(0, 0);
    printw("You Died \n");
    printw("Points: %i", points);
    moveObstacles = false;
    frogLifetime = false;

}
void Win()
{   
    move(frog.x, frog.y);
    move(0, 0);
    printw("You Win! \n");
    printw("Points: %i", points);
    moveObstacles = false;
    frogLifetime = false;

}
void frogAround() { //thread func

frog.x = 10;
frog.y = 24;

moveFrog(frog);

while (frogLifetime) {

	int ch = getch();
	move(frog.x, frog.y);
	printw(" ");
	if (ch == 'd' && frogLifetime == true) {

        if((mvinch(frog.x, frog.y+1)) != '|')
        {
            if((mvinch(frog.x, frog.y+1)) == 'O')
            {
                Death();
                break;
            }
	   // for(int i =0; i<4; i++)
	    if((mvinch(frog.x, frog.y+1)) == 'K')
	    {	
		points++;

	    }

		    frog = frogForward(frog);
        }
	}
	
	if (ch == 'w' && frogLifetime == true) {
        if((mvinch(frog.x-1, frog.y)) != '-')
        {
            if((mvinch(frog.x-1, frog.y)) == 'O')
            {
                Death();
                break;
            }
	    if((mvinch(frog.x-1, frog.y)) == 'K')
	    {	
		points++;
	    }
	    frog = frogLeft(frog);
	    if(frog.x==1)
	    {	
		Win();
	    }       
}
	}
	
	if (ch == 's' && frogLifetime == true) {

        if((mvinch(frog.x+1, frog.y)) != '-')
        {
            if((mvinch(frog.x+1, frog.y)) == 'O')
            {
               Death();
               break;
            }
      	    if((mvinch(frog.x+1, frog.y)) == 'K')
	    {	
		points++;
	    }
		    frog = frogRight(frog);
        }
	}	
	if (ch == 'a' && frogLifetime == true){

        if(mvinch(frog.x, frog.y-1) != '|')
        {
            
            if((mvinch(frog.x, frog.y-1)) == 'O')
            {
                Death();
                break;
                
            }
	    if((mvinch(frog.x, frog.y-1)) == 'K')
	    {	
		points++;
	    }
		    frog = frogBackwards(frog);
        }
	}
        if(frogLifetime==true)
        {
		    moveFrog(frog);
		    refresh();
        }
	}
}
void flyAround()
{
	fly.x = rand() % 19 + 1;
	fly.y = rand() % 29 + 10;
	sitFly(fly);
	while(moveObstacles && fly.x!=frog.x && fly.y!=frog.y)
	{
		sitFly(fly);
		usleep((sec)/18);
	}
}
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
	while(moveObstacles){
		move(dontAvoidThis.x, dontAvoidThis.y);
		for(int i=0; i<3; i++)
		printw("O");
		refresh();
        if(dontAvoidThis.x == frog.x && dontAvoidThis.y+3 == frog.y)
            {
                Death();
            }
		usleep((8*sec)/18);
        if(dontAvoidThis.x == frog.x && dontAvoidThis.y+3 == frog.y)
            {
                Death();
            }
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
	while(moveObstacles){
		move(dontAvoidThis.x, dontAvoidThis.y);
		for(int i=0; i<5; i++)
        {
		    printw("O");
        }
         if(dontAvoidThis.x == frog.x && dontAvoidThis.y+5 == frog.y)
            {
                Death();
            }
		refresh();
		usleep(sec/4);
        if(dontAvoidThis.x == frog.x && dontAvoidThis.y+3 == frog.y)
            {
                Death();
            }
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
		
	}
	printw("          ");
	for(int i=0; i<30; i++)
		printw("-");
}

int main()
{
	srand(time(NULL));
    std::thread thr[5];
	std::thread thr2[2];

	initscr();
	cbreak();
	noecho();
	curs_set(0);

    
	frogThread = std::thread(frogAround); 
    printMap();
	for(int i = 0; i < 4; i++)
	{
		flyThreads[i] = std::thread(flyAround);
	}
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
		flyThreads[i].join();
	} 
    frogThread.join();
	getch();
	//while(true);
	endwin();
}
