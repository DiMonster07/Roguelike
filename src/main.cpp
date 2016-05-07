#include "gamemanager.h"

using namespace std;

int main(int argc, char **argv)
{
	GameManager::instance().initConsole();
	GameManager::instance().createGrids();
	GameManager::instance().gameLoop();
	GameManager::instance().deleteGrids();
	endwin();
	return 0;
}
