#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "units.h"

class GameManager
{
private:
	WINDOW *game_win, *info_win;
public:
	Map map;
	bool is_end_game = false;
	GameManager(const char *name_map);
	static GameManager& instance();
	void initConsole();
	void createGrids();
	void deleteGrids();
	void refreshGrid();
	void refreshInfo();
	int keyCallback(int key);
	void selectStartPos();
	Point findFreePlace(Point lp, Point rp);
	int actorsActions();
	void deleteActor(Actor *actor);
	void generateUnits();
	void spawnActions();
	void gameLoop();
	void gameEnd(int status);
	void freeResources();
	int collide(Actor* left, Actor* right);
};
