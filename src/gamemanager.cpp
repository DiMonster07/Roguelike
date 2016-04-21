#include "gamemanager.h"

const int vis_range = 3;
const int att_range = 1;

const char *dir = "../src/map.txt";

void initColorPairs();

void GameManager::collide(Actor* left, Actor* right)
{
	left->collide(right);
	if (right->is_die())
	{
		int xl = left->getX();
		int yl = left->getY();
		int xr = right->getX();
		int yr = right->getY();
		this->deleteActor(right);
		this->map.map[xr][yr] = left;
		this->map.map[xr][yr]->setCoordinates(xr, yr);
		this->map.map[xl][yl] = new Ground(1, xl, yl);
	}
}

void GameManager::deleteActor(Actor *actor)
{
	for (int i = 0; i < this->actors.size(); i++)
	{
		if (this->actors[i] == actor)
		{
			this->actors.erase(this->actors.begin() + i);
			break;
		}
	}
	delete actor;
}

void GameManager::gameLoop()
{
	this->selectStartPos();
 	this->generateUnits();
 	this->refreshGrid();
	while (1)
	{
		int command = wgetch(this->game_win);
		if (this->keyCallback(command)) break;
		//this->unitsMove();
		this->refreshGrid();
	}
}

void GameManager::unitsMove()
{
	int x_k = this->knight->getX();
	int y_k = this->knight->getY();
	for (int i = 0; i < this->actors.size(); i++)
	{
		int x_m = this->actors[i]->getX();
		int y_m = this->actors[i]->getY();
		if ((abs(x_m - x_k) <= vis_range) && (abs(y_m - y_k) <= vis_range))
		{
			x_m = (x_k - x_m) < 0 ? -1 : 1;
			y_m = (y_k - y_m) < 0 ? -1 : 1;
		}
		else
		{
			x_m = rand() % 3 - 1;
			y_m = rand() % 3 - 1;
		}
		this->actors[i]->move(this->map, x_m, y_m);
		x_m = this->actors[i]->getX();
		y_m = this->actors[i]->getY();
		//if (abs(x_m - x_k) <= 1 && abs(y_m - y_k) <= 1)
		//	this->collide(this->knight, this->actors[i]);
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
	int x = this->knight->getX();
	int y = this->knight->getY();
	while (1)
	{
		int xn = rand() % (this->map.rows - 2) + 1;
		int yn = rand() % (this->map.cols - 2) + 1;
		if ((abs(x - xn) >= this->map.rows / 2 - 1) &&
			(abs(y - yn) >= this->map.cols / 2 - 1) &&
			(this->map.map[xn][yn]->get_symbol() == '.'))
		{
			x = xn;
			y = yn;
			break;
		}
	}
	this->princess = new Princess(1, 0, x, y);
	this->map.addActor(this->princess);
	int i = 0;
	while(i < 30)
	{
		x = rand() % (this->map.rows - 1) + 1;
		y = rand() % (this->map.cols - 1) + 1;
		if (this->map.map[x][y]->get_symbol() == '.')
		{
			this->addActor('Z', x, y);
			i++;
		}
	}
}

int GameManager::keyCallback(int key)
{
	int x = this->knight->getX();
	int y = this->knight->getY();
	switch(key)
	{
		case KEY_UP: this->collide(this->knight, this->map.map[x - 1][y]);
			break;
		case KEY_DOWN: this->collide(this->knight, this->map.map[x + 1][y]);
			break;
		case KEY_RIGHT: this->collide(this->knight, this->map.map[x][y + 1]);
			break;
		case KEY_LEFT: this->collide(this->knight, this->map.map[x][y - 1]);
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
	mvwprintw(this->info_win, 1, 0, "Health: %d", this->knight->get_hp());
	mvwprintw(this->info_win, 2, 0, "Damage: %d", this->knight->get_damage());
	mvwprintw(this->info_win, 3, 0, "Сoordinate: %d %d", this->knight->getY(),
		this->knight->getX());
	//mvwprintw(this->info_win, 4, 0, "Vector size: %d", this->actors.size());
	wrefresh(this->info_win);
}

void GameManager::selectStartPos()
{
	mvwprintw(this->game_win, 0, 1, "%s\n %s",
 		"Please, select you start position.",
 		"After selected press SPACE. Press any key now...");
 	wrefresh(this->game_win);
 	wgetch(this->game_win);
	this->knight = new Knight(100, 3, 1, 1);
	this->map.map[1][1] = this->knight;
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

void GameManager::addActor(char c, int x, int y)
{
	 switch(c)
	 {
	 	case 'Z': this->actors.push_back(new Zombie(4, 2, x, y)); break;
	 	case 'D': this->actors.push_back(new Dragon(70, 25, x, y)); break;
	 }
	 this->map.addActor(this->actors[this->actors.size() - 1]);
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
