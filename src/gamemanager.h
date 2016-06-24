#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include <string>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include "units.h"
#include "mapconstructor.h"

class GameManager
{
private:
	WINDOW *game_win, *info_win;
public:
	Map map;
	bool is_end_game = false;
	MapConstructor map_constructor();
	GameManager(std::string name_map);
	static GameManager& instance();
	void initConsole();
	void createGrids();
	void deleteGrids();
	void refreshGrid();

	void refreshInfo();
	int readActorsInfo();

	int gameCallback(int key);
	int menuCallback(int key);

	void selectStartPos();
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

	void printMenuMap(std::vector<std::string>maps_list, int cursor);
	std::string selectMap();
	std::vector<std::string> getFilesList(std::string directory,
										  std::string file_extension);
	void mapConstruct();
};
