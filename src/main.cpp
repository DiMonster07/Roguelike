
#include "gamemanager.h"

using namespace std;

int main(int argc, char **argv)
{
	GameManager::instance().initConsole();
	GameManager::instance().createGrids();
	GameManager::instance().gameLoop();
	GameManager::instance().deleteGrids();
	endwin();
	// int n = 2;
    // vector<Actor*> actors;
    // Knight* knight = new Knight(100, 3, 1, 1);
    // actors.push_back(knight);
    // actors.push_back(new Ground(0, 0, 0));
	//
    // cout << ((Character*)actors[0])->get_hp() << endl;
    // actors[0]->collide(actors[1]);
    // cout << ((Character*)actors[0])->get_hp() << endl;
    // cout << "All done!" << endl;
	return 0;
}
