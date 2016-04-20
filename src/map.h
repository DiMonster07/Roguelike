#pragma once
#include <ncurses.h>
#include <panel.h>
#include <iostream>
#include <vector>

class Actor;
class Character;
class Knight;
class Princess;
class Monster;
class Environment;
class Wall;
class Ground;

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
