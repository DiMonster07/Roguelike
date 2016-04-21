#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "units.h"
#include "map.h"

enum COLORS_UNITS
{
	WALL_COLOR = 1,
	GROUND_COLOR = 2,
	KNIGHT_COLOR = 3,
	PRINCESS_COLOR = 4,
	ZOMBIE_COLOR = 5,
	DRAGON_COLOR = 6,
	BASE_COLOR = 7
};

#define KEY_DAMAGE ' '

class GameManager
{
private:
	WINDOW *game_win, *info_win;
public:
	Map map;
	Knight *knight;
	Princess *princess;
	std::vector<Actor*> actors;
	GameManager(const char *name_map);
	static GameManager& instance();
	void initConsole();
	void createGrids();
	void deleteGrids();
	void refreshGrid();
	void refreshInfo();
	int keyCallback(int key);
	void selectStartPos();
	void unitsMove();
	void addActor(char c, int x, int y);
	void deleteActor(Actor *actor);
	void generateUnits();
	void knightAttack();
	void gameLoop();
	void collide(Actor* left, Actor* right);
};
