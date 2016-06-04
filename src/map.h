#pragma once
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>
#include "meta.h"
#include "point.h"

class Map
{
public:
	bool sd;
	int cols, rows;
	Knight *knight;
	Princess *princess;
	std::vector<Spawn*> spawns;
	std::vector<Actor*> actors;
	std::vector< std::vector<Actor*> > map;
	Map() {};
	Map(const char *name_map);
	void changeActor(Actor *actor);
	void addSpawn();
	Point findFreePlace(Point lp, Point rp);
	void addActor(char c, int x, int y);
	void printMap(WINDOW *win);
};
