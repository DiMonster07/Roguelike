#include "gamemanager.h"
#include "config.h"

int main(int argc, char **argv)
{
	Config::instance().parse("../src/config.cfg");
	Config::instance().setVariables();
	GameManager::instance().initConsole();
	GameManager::instance().createGrids();
	GameManager::instance().menuLoop();
	GameManager::instance().deleteGrids();
	endwin();
	return 0;
}
