#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "units.h"
#include "map.h"

enum COLORS_UNITS 
{ 
	WALL = 1, 
	LEA = 2, 
	KNIGHT = 3, 
	PRINCESS = 4, 
	ZOMBIE = 5, 
	DRAGON = 6,
	BASE = 7
};

class GameManager
{
public:
	Map map;
	std::vector<Character*> heroes;
	std::vector<Character*> monsters;
	GameManager(const char *name_map);
	int keyCallback(int key);
	void selectStartPos(WINDOW *win);
	void addUnit(char c, int x, int y);
	void generateUnits();
	void refreshGrid();
	void refreshInfo();
};