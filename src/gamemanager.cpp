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
		Point pl = left->get_point();
		Point pr = right->get_point();
		this->deleteActor(right);
		this->map.map[pr.x][pr.y] = left;
		this->map.map[pr.x][pr.y]->set_point(pr);
		this->map.map[pl.x][pl.y] = new Ground(1, pl.x, pl.y);
	}
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
		this->unitsMove();
		this->refreshGrid();
	}
}

void GameManager::unitsMove()
{
	Point p_knight = this->knight->get_point();
	for (int i = 0; i < this->actors.size(); i++)
	{
		Point offset = this->actors[i]->get_point();
		if ((abs(offset.x - p_knight.x) <= vis_range) &&
			(abs(offset.y - p_knight.y) <= vis_range))
		{
			offset.x = (p_knight.x - offset.x) < 0 ? -1 : 1;
			offset.y = (p_knight.y - offset.y) < 0 ? -1 : 1;
		}
		else
		{
			offset.x = rand() % 3 - 1;
			offset.y = rand() % 3 - 1;
		}
		Point p_act = this->actors[i]->get_point();
		this->collide(this->actors[i],
			this->map.map[p_act.x + offset.x][p_act.y + offset.y]);
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
	Point pnt = this->knight->get_point();
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
	this->princess = new Princess(1, 0, pnt.x, pnt.y);
	this->map.addActor(this->princess);
	int i = 0;
	while(i < 30)
	{
		pnt.x = rand() % (this->map.rows - 1) + 1;
		pnt.y = rand() % (this->map.cols - 1) + 1;
		if (this->map.map[pnt.x][pnt.y]->get_symbol() == '.')
		{
			this->addActor('Z', pnt.x, pnt.y);
			i++;
		}
	}
}

int GameManager::keyCallback(int key)
{
	Point pnt = this->knight->get_point();
	switch(key)
	{
		case KEY_UP:
			this->collide(this->knight, this->map.map[pnt.x - 1][pnt.y]);
			break;
		case KEY_DOWN:
			this->collide(this->knight, this->map.map[pnt.x + 1][pnt.y]);
			break;
		case KEY_RIGHT:
			this->collide(this->knight, this->map.map[pnt.x][pnt.y + 1]);
			break;
		case KEY_LEFT:
			this->collide(this->knight, this->map.map[pnt.x][pnt.y - 1]);
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
	Point pnt = this->knight->get_point();
	mvwprintw(this->info_win, 3, 0, "Сoordinate: %d %d", pnt.y, pnt.x);
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
