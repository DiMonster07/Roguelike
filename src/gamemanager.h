#pragma once
#include <unistd.h>
#include "units.h"
#include "mapmanager.h"

class GameManager
{
private:
	WINDOW *main_win, *info_win;
public:
	Map map;
	bool is_end_game = false;
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
	std::string selectNameMap(int size_list);
	void mapConstruct();
};
