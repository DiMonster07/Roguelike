#include <stdio.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "gamemanager.h"


const char *dir = "map.txt";

void initColorPairs();

int main(int argc, char **argv)
{
	initscr();
	curs_set(0);
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	WINDOW *win = newwin(30, 80, 0, 0);
	clear();
	start_color();
	initColorPairs();
 	GameManager Manager(dir);
 	mvprintw(0, 0, "%s", "Please, select you start position. After selected press SPACE");
 	getch();
 	Manager.selectStartPos(win);
 	Manager.generateUnits();
 	Manager.refreshGrid();
	while (1)
	{
		int command = getch();
		if (Manager.keyCallback(command)) break;
		Manager.unitsMove();
		Manager.refreshGrid();
	}
	endwin();
	return 0;
}

void initColorPairs()
{
	init_pair(BASE, 7, 0);
	init_pair(WALL, 0, 0);                    
	init_pair(LEA, 7, 7);                     
	init_pair(KNIGHT, 1, 7);                  
	init_pair(PRINCESS, 7, 5);                
	init_pair(ZOMBIE, 2, 7);                  
	init_pair(DRAGON, 1, 0);                  
}
/*
		COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
*/