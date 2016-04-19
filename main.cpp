#include <ctime>
#include <stdlib.h>
#include "gamemanager.h"

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
	srand(time(0));
	GameManager::instance().createGrids();
	keypad(GameManager::instance().game_win, TRUE);
 	mvwprintw(GameManager::instance().game_win, 0, 1, "%s\n %s", 
 		"Please, select you start position.", 
 		"After selected press SPACE. Press any key now...");
 	wrefresh(GameManager::instance().game_win);
 	wgetch(GameManager::instance().game_win);
 	GameManager::instance().selectStartPos();
 	GameManager::instance().generateUnits();
 	GameManager::instance().refreshGrid();
	while (1)
	{
		int command = wgetch(GameManager::instance().game_win);
		if (GameManager::instance().keyCallback(command)) break;
		GameManager::instance().unitsMove();
		GameManager::instance().refreshGrid();
	}
	GameManager::instance().deleteGrids();
	endwin();
	return 0;
}

void initColorPairs()
{
	init_pair(BASE, 7, 0);
	init_pair(WALL, 0, 0);
	init_pair(GROUND, 7, 7);
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