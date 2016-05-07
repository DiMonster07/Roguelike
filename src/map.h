#pragma once
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>
#include "meta.h"

class Map
{
public:
	bool sd;
	int cols, rows;
	Knight *knight;
	Princess *princess;
	std::vector<Actor*> actors;
	std::vector< std::vector<Actor*> > map;
	Map() {};
	Map(const char *name_map);
	void addActor(Actor *actor);
	void printMap(WINDOW *win);
};
