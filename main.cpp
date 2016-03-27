#include <stdio.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "gamemanager.h"
#include <stdlib.h>
#include <ctime>
#include <unistd.h>


const char *dir = "map.txt";

void initColorPairs();

int main(int argc, char **argv)
{
	int x, y;
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	start_color();
	initColorPairs();
	clear();
	GameManager Manager(dir);
	Manager.createWins();
	keypad(Manager.game_win, TRUE);
 	mvwprintw(Manager.game_win, 0, 1, "%s\n %s", "Please, select you start position.", 
 		"After selected press SPACE. Press any key now...");
 	wrefresh(Manager.game_win);
 	wgetch(Manager.game_win);
 	Manager.selectStartPos();
 	Manager.generateUnits();
 	Manager.refreshGrid();
	while (1)
	{
		int command = wgetch(Manager.game_win);
		if (Manager.keyCallback(command)) break;
		Manager.unitsMove();
		Manager.refreshGrid();
	}
	delwin(Manager.game_win);
	delwin(Manager.info_win);
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