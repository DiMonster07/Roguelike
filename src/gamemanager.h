#pragma once
#include <unistd.h>
#include "units.h"
#include "mapmanager.h"

class GameManager
{
private:
	WINDOW *main_win, *info_win;
	int tsizeX, tsizeY;
	std::string map_name = DEFAULT_MAP_NAME;
public:
	Map map;
	bool is_end_game = false;
	GameManager() { };
	static GameManager& instance();
	void mapLoad(std::string map_name);
	void initConsole();
	void createGrids();
	void deleteGrids();
	void refreshGrid();
	void tsizeUpdate();

	void refreshInfo();
	int readActorsInfo();

	int gameCallback(int key);
	int menuCallback(int key);

	void selectStartPos();
	void selectMap();
	int collide(Actor* left, Actor* right);
	Point findFreePlace(Point lp, Point rp);
	int actorsActions();
	void deleteActor(Actor *actor);
	void spawnActions();
	void generateUnits();

	void gameLoop();
	void menuLoop();
	void printMenu();
	void gameEnd(int status);
	void freeResources();
};
