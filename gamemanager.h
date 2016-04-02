#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "units.h"
#include "map.h"

enum COLORS_UNITS 
{ 
	WALL = 1, 
	GROUND = 2, 
	KNIGHT = 3, 
	PRINCESS = 4, 
	ZOMBIE = 5, 
	DRAGON = 6,
	BASE = 7
};

#define KEY_DAMAGE ' '

class GameManager
{
public:
	WINDOW *game_win, *info_win;
	Map map;
	Knight *knight;
	Princess *princess;
	std::vector<Actor*> actors;
	static GameManager& instance();
	GameManager(const char *name_map);
	void collide(Actor* left, Actor* right);
	void createGrids();
	void deleteGrids();
	Actor* getActor(int x, int y);
	int keyCallback(int key);
	void unitsMove();
	void selectStartPos();
	void addActor(char c, int x, int y);
	void generateUnits();
	void knightAttack();
	void refreshGrid();
	void refreshInfo();
};