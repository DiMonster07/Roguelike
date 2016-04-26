#pragma once
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>
#include "units.h"

class Map
{
public:
	bool sd;
	int cols, rows;
	std::vector< std::vector<Actor*> > map;
	Map() {};
	Map(const char *name_map);
	void addActor(Actor *actor);
	void printMap(WINDOW *win);
};
