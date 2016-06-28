#include "gamemanager.h"

int main(int argc, char **argv)
{
	setlocale (LC_ALL,"");
	if (!GameManager::instance().readActorsInfo())
	{
		GameManager::instance().initConsole();
		GameManager::instance().createGrids();
		GameManager::instance().menuLoop();
		GameManager::instance().deleteGrids();
		endwin();
    };
	return 0;
}
