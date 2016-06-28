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
	Knight *knight = NULL;
	Princess *princess = NULL;
	std::vector<Spawn*> spawns;
	std::vector<Actor*> actors;
	std::vector<std::vector<Actor*>> map;
	Map() {};
	Map(std::string name_map);
	void changeActor(Actor *actor);
	void addSpawn();
	Point findFreePlace();
	Point findFreePlace(Point lp, Point rp);
	void addActor(char c, Point p);
	Point get_right_ang();
	Point pointValidation(Point p, int side);
	void printMap(WINDOW *win);
};
