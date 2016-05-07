#include "gamemanager.h"
const char *dir = "../src/map.txt";

void initColorPairs();

void GameManager::collide(Actor* left, Actor* right)
{
	left->collide(right);
	if (right->is_die())
	{
		if (right == this->map.knight)
		{
			is_end_game = false;
			return;
		};
		Point pl = left->get_point();
		Point pr = right->get_point();
		this->deleteActor(right);
		this->map.map[pr.x][pr.y] = left;
		this->map.map[pr.x][pr.y]->set_point(pr);
		this->map.map[pl.x][pl.y] = new Ground(1, pl.x, pl.y);
	}
}

void GameManager::actorsActions()
{
	for (int i = 0; i < this->map.actors.size(); i++)
	{
		Point direction = this->map.actors[i]->get_direction(this->map);
		Point p_actor = this->map.actors[i]->get_point();
		this->collide(this->map.actors[i],
			this->map.map[p_actor.x + direction.x][p_actor.y + direction.y]);
	}
}

void GameManager::knightAttack()
{
	// int x_a = this->knight->getX();
	// int y_a = this->knight->getY();
	// for (int x = x_a - att_range; x <= x_a + att_range; x++)
	// 	for (int y = y_a - att_range; y <= y_a + att_range; y++)
	// 		if (((x_a != x) || (y_a != y)) &&
	// 			(this->map.map[y][x].get_symbol() != WALL_SYMBOL))
	// 		{
	// 			int a;
	// 			switch (this->map.map[y][x].get_symbol())
	// 			{
	// 				case PRINCESS_SYMBOL: break;
	// 				case ZOMBIE_SYMBOL:
	// 					this->collide(this->getActor(x, y), this->knight);
	// 					break;
	// 				case DRAGON_SYMBOL: break;
	// 			}
	// 		}
}

void GameManager::generateUnits()
{
	Point pnt = this->map.knight->get_point();
	while (1)
	{
		int xn = rand() % (this->map.rows - 2) + 1;
		int yn = rand() % (this->map.cols - 2) + 1;
		if ((abs(pnt.x - xn) >= this->map.rows / 2 - 1) &&
			(abs(pnt.y - yn) >= this->map.cols / 2 - 1) &&
			(this->map.map[xn][yn]->get_symbol() == '.'))
		{
			pnt.x = xn;
			pnt.y = yn;
			break;
		}
	}
	this->map.princess = new Princess(1, 0, pnt.x, pnt.y);
	this->map.addActor(this->map.princess);
	for (int i = 0; i < 30; i++)
	{
		Point pnt = this->findFreePlace(Point(1, 1), Point(28, 58));
		this->addActor('Z', pnt.x, pnt.y);
	}
}

int GameManager::keyCallback(int key)
{
	Point pnt = this->map.knight->get_point();
	switch(key)
	{
		case KEY_UP:
			this->collide(this->map.knight, this->map.map[pnt.x - 1][pnt.y]);
			break;
		case KEY_DOWN:
			this->collide(this->map.knight, this->map.map[pnt.x + 1][pnt.y]);
			break;
		case KEY_RIGHT:
			this->collide(this->map.knight, this->map.map[pnt.x][pnt.y + 1]);
			break;
		case KEY_LEFT:
			this->collide(this->map.knight, this->map.map[pnt.x][pnt.y - 1]);
			break;
		//case KEY_DAMAGE: this->knightAttack(); break;
		case 27: return 1;
	}
	return 0;
}

void GameManager::refreshInfo()
{
	wclear(this->info_win);
	mvwprintw(this->info_win, 0, 0, "%s", "INFO");
	mvwprintw(this->info_win, 1, 0, "Health: %d", this->map.knight->get_hp());
	mvwprintw(this->info_win, 2, 0, "Damage: %d", this->map.knight->get_damage());
	Point pnt = this->map.knight->get_point();
	mvwprintw(this->info_win, 3, 0, "Сoordinate: %d %d", pnt.y, pnt.x);
	wrefresh(this->info_win);
}

void GameManager::selectStartPos()
{
	mvwprintw(this->game_win, 0, 1, "%s\n %s",
 		"Please, select you start position.",
 		"After selected press SPACE. Press any key now...");
 	wrefresh(this->game_win);
 	wgetch(this->game_win);
	this->map.knight = new Knight(100, 3, 1, 1);
	this->map.map[1][1] = this->map.knight;
	this->refreshGrid();
	while(1)
	{
		int command = wgetch(this->game_win);
		if (command == ' ') break;
		this->keyCallback(command);
		this->refreshGrid();
	}
	wrefresh(this->game_win);
	mvwprintw(this->game_win, 0, 0, "%s", "Please press any key. Good luck!");
	wgetch(this->game_win);
	clear();
}

void GameManager::gameLoop()
{
	this->selectStartPos();
 	this->generateUnits();
 	this->refreshGrid();
	while (!this->is_end_game)
	{
		int command = wgetch(this->game_win);
		if (this->keyCallback(command)) break;
		this->actorsActions();
		this->refreshGrid();
	}
}

void freeResources()
{

}

Point GameManager::findFreePlace(Point lp, Point rp)
{
	int c = 0;
	for (int i = lp.x; i <= rp.x; i++)
		for (int j = lp.y; j <= rp.y; j++)
			if (this->map.map[i][j]->get_symbol() == GROUND_SYMBOL) c++;
	int num = rand() % c + 1;
	c = 0;
	for (int i = lp.x; i <= rp.x; i++)
		for (int j = lp.y; j <= rp.y; j++)
		{
			if (this->map.map[i][j]->get_symbol() == GROUND_SYMBOL) c++;
			if (c == num) return this->map.map[i][j]->get_point();
		}
}

void GameManager::addActor(char c, int x, int y)
{
	 switch(c)
	 {
	 	case 'Z': this->map.actors.push_back(new Zombie(4, 2, x, y)); break;
	 	case 'D': this->map.actors.push_back(new Dragon(70, 25, x, y)); break;
	 }
	 this->map.addActor(this->map.actors[this->map.actors.size() - 1]);
}

void GameManager::deleteActor(Actor *actor)
{
	for (int i = 0; i < this->map.actors.size(); i++)
	{
		if (this->map.actors[i] == actor)
		{
			this->map.actors.erase(this->map.actors.begin() + i);
			break;
		}
	}
	delete actor;
}

void GameManager::refreshGrid()
{
	this->map.printMap(this->game_win);
	this->refreshInfo();
}

void GameManager::initConsole()
{
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	start_color();
	initColorPairs();
	clear();
	srand(time(0));
}

void GameManager::createGrids()
{
	this->game_win = newwin(30, 60, 0, 0);
	this->info_win = newwin(30, 20, 0, 61);
	keypad(this->game_win, TRUE);
}

void GameManager::deleteGrids()
{
	delwin(this->game_win);
	delwin(this->info_win);
}

GameManager::GameManager(const char *name_map)
{
	this->map = Map(name_map);
}

GameManager& GameManager::instance()
{
	static GameManager manager(dir);
	return manager;
}

void initColorPairs()
{
	init_pair(WALL_COLOR, 0, 0);
	init_pair(GROUND_COLOR, 7, 7);
	init_pair(KNIGHT_COLOR, 1, 7);
	init_pair(PRINCESS_COLOR, 7, 5);
	init_pair(ZOMBIE_COLOR, 2, 7);
	init_pair(DRAGON_COLOR, 1, 0);
	init_pair(ZOMBIES_SPAWN_COLOR, 0, 2);
	init_pair(DRAGONS_SPAWN_COLOR, 0, 1);
	init_pair(WIZARD_COLOR, 7, 4);
	init_pair(BASE_COLOR, 7, 0);
}
/*
		COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
*/
