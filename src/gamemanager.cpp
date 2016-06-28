#include "gamemanager.h"

void initColorPairs();

int GameManager::collide(Actor* left, Actor* right)
{
	left->collide(right);
	return this->isActorsDied(left, right);
};

int GameManager::isActorsDied(Actor* left, Actor* right)
{
	Point pl = left->get_point();
	Point pr = right->get_point();
	if (right->is_die())
	{
		if (right == this->map.knight) return GAME_LOSE;
		if (right == this->map.princess) return GAME_WIN;
		this->deleteActor(right);
		this->map.map[pr.y][pr.x] = left;
		this->map.map[pr.y][pr.x]->set_point(pr);
		this->map.map[pl.y][pl.x] = new Ground(1, pl);
	}
	if (left->is_die())
	{
		pl = left->get_point();
		this->map.map[pl.y][pl.x] = new Ground(1, pl);
		this->deleteActor(left);
	}
	return GAME_CONTINUE;
};

int GameManager::actorsActions()
{
	for (int i = 0; i < this->map.actors.size(); i++)
	{
		if (this->map.actors[i]->get_symbol() != MEDKIT_SYMBOL)
		{
			Point direction = this->map.actors[i]->get_direction(this->map);
			Point p = this->map.actors[i]->get_point() + direction;
			int status = this->collide(this->map.actors[i], this->map.map[p.y][p.x]);
			if (status) return status;
			if (this->map.actors[i]->get_symbol() == WIZARD_SYMBOL)
				this->map.actors[i]->specialSkill(this->map);
		}
	}
	return GAME_CONTINUE;
};

void GameManager::spawnActions()
{
	for(Spawn* s: this->map.spawns)
		s->action(this->map);
};

int GameManager::gameCallback(int key)
{
	Point pnt = this->map.knight->get_point();
	switch(key)
	{
		case KEY_UP:
			return this->collide(this->map.knight,
				   this->map.map[pnt.y - 1][pnt.x]);
			break;
		case KEY_DOWN:
			return this->collide(this->map.knight,
				   this->map.map[pnt.y + 1][pnt.x]);
			break;
		case KEY_RIGHT:
			return this->collide(this->map.knight,
				   this->map.map[pnt.y][pnt.x + 1]);
			break;
		case KEY_LEFT:
			return this->collide(this->map.knight,
				   this->map.map[pnt.y][pnt.x - 1]);
			break;
		case 27: return GAME_LOSE;
	}
	return GAME_CONTINUE;
};

void GameManager::gameLoop()
{
	std::string map_name;
	if (!MapManager::instance().selectMap(&map_name)) return;
	this->mapLoad(map_name);
	this->selectStartPos();
 	this->generateUnits();
 	this->refreshGrid();
	while (!this->is_end_game)
	{
		int command = wgetch(this->main_win);
		if (int status = this->gameCallback(command))
		{
			this->gameEnd(status);
			break;
		}
		else
		{
			if(int status = this->actorsActions())
			{
				this->gameEnd(status);
				break;
			}
			this->spawnActions();
			this->refreshGrid();
		}
		usleep(30000);
	}
};

void GameManager::selectMap()
{
	int command;
	wclear(this->main_win);
	wrefresh(this->main_win);
};

void GameManager::selectStartPos()
{
	wclear(this->main_win);
	mvwprintw(this->main_win, 0, 1, "%s\n %s",
 		"Please, select you start position.",
 		"After selected press SPACE");
	wrefresh(this->main_win);
	if (this->map.knight == NULL)
	{
		this->map.knight = new Knight(knight_health, knight_damage, Point(1, 1));
		this->map.map[1][1] = this->map.knight;
	}
	this->refreshGrid();
	while(1)
	{
		int command = wgetch(this->main_win);
		if (command == KEY_SPACE) break;
		this->gameCallback(command);
		this->refreshGrid();
	}
	wrefresh(this->main_win);
	mvwprintw(this->main_win, 0, 0, "%s", "Please press any key. Good luck!");
};

void GameManager::generateUnits()
{
	Point pnt = this->map.knight->get_point();
	int f = wgetch(this->main_win);
	while (1)
	{
		int xn = rand() % (this->map.cols - 2) + 1;
		int yn = rand() % (this->map.rows - 2) + 1;
		if ((abs(pnt.x - xn) >= this->map.cols / 2 - 1) &&
			(abs(pnt.y - yn) >= this->map.rows / 2 - 1) &&
			(this->map.map[yn][xn]->get_symbol() == '.'))
		{
			pnt = Point(xn, yn);
			break;
		}
	}
	if (this->map.princess == NULL)
	{
		this->map.princess = new Princess(1, 0, pnt);
		this->map.changeActor(this->map.princess);
	}
	for (int i = 0; i < 15; i++)
	{
		pnt = this->map.findFreePlace();
		this->map.addActor(ZOMBIE_SYMBOL, pnt);
	}
	this->map.spawns.push_back(new SpawnMedkit(1, medkit_spawn_timer, Point(0, 0)));
};

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
};

void GameManager::gameEnd(int status)
{
	wclear(this->main_win);
	wclear(this->info_win);
	switch (status)
	{
		case GAME_WIN:
			mvwprintw(this->main_win, 3, 3, "%s", "You WIN! Congratulations!");
			break;
		case GAME_LOSE:
			mvwprintw(this->main_win, 3, 3, "%s", "You LOSE! Sorry =(");
			break;
	};
	wrefresh(this->main_win);
	wrefresh(this->info_win);
	usleep(1000000);
};

void GameManager::menuLoop()
{
	MapManager::instance().initialize(this->main_win, this->info_win);
	while(true)
	{
		this->printMenu();
		int command = wgetch(this->main_win);
		if (!this->menuCallback(command)) break;
	}
};

int GameManager::menuCallback(int key)
{
	switch(key)
	{
		case GAME_START: this->gameLoop(); break;
		case CREATE_MAP: MapManager::instance().mapConstruct(); break;
		case GAME_EXIT: return 0; break;
	}
	return 1;
};

void GameManager::printMenu()
{
	wclear(this->info_win);
	wclear(this->main_win);
	mvwprintw(this->main_win, 1, 3, "%s", "MENU:");
	mvwprintw(this->main_win, 3, 3, "%s", "1 - Start game");
	mvwprintw(this->main_win, 4, 3, "%s", "2 - Create/Change map");
	mvwprintw(this->main_win, 5, 3, "%s", "0 - Exit");
	wrefresh(this->main_win);
	wrefresh(this->info_win);
};

int GameManager::readActorsInfo()
{
	return 0;
};

////////////////////////////////////BS/////////////////////////////////////////

void GameManager::refreshGrid()
{
	this->map.printMap(this->main_win);
	this->refreshInfo();
};

void GameManager::refreshInfo()
{
	wclear(this->info_win);
	mvwprintw(this->info_win, 0, 0, "%s", "INFO");
	mvwprintw(this->info_win, 1, 0, "Health: %d", this->map.knight->get_hp());
	mvwprintw(this->info_win, 2, 0, "Damage: %d", this->map.knight->get_damage());
	Point pnt = this->map.knight->get_point();
	mvwprintw(this->info_win, 3, 0, "Coordinate: %d %d", pnt.y, pnt.x);
	mvwprintw(this->info_win, 4, 0, "Medkits: %d", this->map.getActorsCount(MEDKIT_SYMBOL));
	wrefresh(this->info_win);
};

void GameManager::tsizeUpdate()
{
	getmaxyx(stdscr, this->tsizeY, this->tsizeX);
};

void GameManager::createGrids()
{
	this->tsizeUpdate();
	this->main_win = newwin(this->tsizeY, this->tsizeX - INFO_WIN_WIDTH, 0, 0);
	this->info_win = newwin(this->tsizeY, INFO_WIN_WIDTH, 0, this->tsizeX -
															 INFO_WIN_WIDTH + 1);
	keypad(this->main_win, TRUE);
};

void GameManager::deleteGrids()
{
	delwin(this->main_win);
	delwin(this->info_win);
};

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
	this->tsizeUpdate();
};

void GameManager::mapLoad(std::string map_name)
{
	map = Map(map_name);
};

GameManager& GameManager::instance()
{
	static GameManager manager;
	return manager;
};

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
	init_pair(MEDKIT_COLOR, 1, 7);
	init_pair(WIZARD_COLOR, 7, 4);
	init_pair(FIREBALL_COLOR, 7, 4);
	init_pair(BASE_COLOR, 7, 0);
};
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
