#include "gamemanager.h"
#include <unistd.h>
const char *dir = "../src/map.txt";

void initColorPairs();

int GameManager::collide(Actor* left, Actor* right)
{
	left->collide(right);
	if (right->is_die())
	{
		if (right == this->map.knight) return GAME_LOSE;
		if (right == this->map.princess) return GAME_WIN;
		if (right->get_symbol() == BONUS_HEALTH_SYMBOL)
			this->map.spawns.back()->dec();
		Point pl = left->get_point();
		Point pr = right->get_point();
		this->deleteActor(right);
		this->map.map[pr.x][pr.y] = left;
		this->map.map[pr.x][pr.y]->set_point(pr);
		this->map.map[pl.x][pl.y] = new Ground(1, pl);
	}
	return GAME_CONTINUE;
};

int GameManager::actorsActions()
{
	for (int i = 0; i < this->map.actors.size(); i++)
	{
		Point direction = this->map.actors[i]->get_direction(this->map);
		Point p = this->map.actors[i]->get_point() + direction;
		int status = this->collide(this->map.actors[i], this->map.map[p.x][p.y]);
		if(status) return status;
	}
	return GAME_CONTINUE;
};

void GameManager::spawnActions()
{

	for(int i = 0; i < this->map.spawns.size(); i++)
	{
		this->map.spawns[i]->action(this->map);
	}
};

int GameManager::keyCallback(int key)
{
	Point pnt = this->map.knight->get_point();
	switch(key)
	{
		case KEY_UP:
			return this->collide(this->map.knight,
				   this->map.map[pnt.x - 1][pnt.y]);
			break;
		case KEY_DOWN:
			return this->collide(this->map.knight,
				   this->map.map[pnt.x + 1][pnt.y]);
			break;
		case KEY_RIGHT:
			return this->collide(this->map.knight,
				   this->map.map[pnt.x][pnt.y + 1]);
			break;
		case KEY_LEFT:
			return this->collide(this->map.knight,
				   this->map.map[pnt.x][pnt.y - 1]);
			break;
		case 27: return GAME_LOSE;
	}
	return GAME_CONTINUE;
};

void GameManager::gameLoop()
{
	this->selectStartPos();
 	this->generateUnits();
 	this->refreshGrid();
	while (!this->is_end_game)
	{
		int command = wgetch(this->game_win);
		if (int status = this->keyCallback(command))
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
	}
};

void GameManager::refreshInfo()
{
	wclear(this->info_win);
	mvwprintw(this->info_win, 0, 0, "%s", "INFO");
	mvwprintw(this->info_win, 1, 0, "Health: %d", this->map.knight->get_hp());
	mvwprintw(this->info_win, 2, 0, "Damage: %d", this->map.knight->get_damage());
	Point pnt = this->map.knight->get_point();
	mvwprintw(this->info_win, 3, 0, "Сoordinate: %d %d", pnt.y, pnt.x);
	mvwprintw(this->info_win, 4, 0, "Bonuses: %d", this->map.spawns.back()->get_count());
	wrefresh(this->info_win);
};

void GameManager::selectStartPos()
{
	mvwprintw(this->game_win, 0, 1, "%s\n %s",
 		"Please, select you start position.",
 		"After selected press SPACE");
 	wrefresh(this->game_win);
 	wgetch(this->game_win);
	this->map.knight = new Knight(knight_health, 3, Point(1, 1));
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
};

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
			pnt = Point(xn, yn);
			break;
		}
	}
	this->map.princess = new Princess(1, 0, pnt);
	this->map.changeActor(this->map.princess);
	for (int i = 0; i < 15; i++)
	{
		Point pnt = this->map.findFreePlace(LEFT_ANG, RIGHT_ANG);
		this->map.addActor(ZOMBIE_SYMBOL, pnt);
	}
	this->map.spawns.push_back(new SpawnHealth(1, health_spawn_timer, Point(0, 0)));
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
	delete actor;
};

void GameManager::gameEnd(int status)
{
	wclear(this->game_win);
	wclear(this->info_win);
	switch (status)
	{
		case GAME_WIN:
			mvwprintw(this->game_win, 3, 3, "%s", "You WIN! Congratulations!");
			break;
		case GAME_LOSE:
			mvwprintw(this->game_win, 3, 3, "%s", "You LOSE! Sorry =(");
			break;
	};
	wrefresh(this->game_win);
	wrefresh(this->info_win);
	usleep(1000000);
};

void GameManager::refreshGrid()
{
	this->map.printMap(this->game_win);
	this->refreshInfo();
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
};

void GameManager::createGrids()
{
	this->game_win = newwin(30, 60, 0, 0);
	this->info_win = newwin(30, 20, 0, 61);
	keypad(this->game_win, TRUE);
};

void GameManager::deleteGrids()
{
	delwin(this->game_win);
	delwin(this->info_win);
};

GameManager::GameManager(const char *name_map)
{
	this->map = Map(name_map);
};

GameManager& GameManager::instance()
{
	static GameManager manager(dir);
	return manager;
};

int GameManager::readActorsInfo()
{
	
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
	init_pair(WIZARD_COLOR, 7, 4);
	init_pair(BONUS_HEALTH_COLOR, 1, 7);
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
