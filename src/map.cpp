#include "map.h"
#include "gamemanager.h"
#include "units.h"
#include <malloc.h>
#include <fstream>
#include <iostream>

Map::Map(std::string name_map)
{
	std::ifstream input(name_map);
	char c;
	input >> this->rows;
	input >> this->cols;
	for (int i = 0; i < this->rows; i++)
	{
		std::vector<Actor*> row;
		for (int j = 0; j < this->cols; j++)
		{
			Actor* new_actor;
			SpawnDragons* new_spawnd;
			SpawnZombies* new_spawnz;
			input >> c;
			switch(c)
			{
				case WALL_SYMBOL:
					new_actor = new Wall(3, Point(i, j));
					row.push_back(new_actor);
					break;
				case GROUND_SYMBOL:
					new_actor = new Ground(1, Point(i, j));
					row.push_back(new_actor);
					break;
				case DRAGONS_SPAWN_SYMBOL:
					new_spawnd = new SpawnDragons(60, dragon_spawn_timer,
						Point(i, j));
					this->spawns.push_back(new_spawnd);
					row.push_back(new_spawnd);
					break;
				case ZOMBIES_SPAWN_SYMBOL:
					new_spawnz = new SpawnZombies(30, zombies_spawn_timer,
						Point(i, j));
					this->spawns.push_back(new_spawnz);
					row.push_back(new_spawnz);
					break;
			}
		}
		map.push_back(row);
	}
};

Point Map::findFreePlace(Point lp, Point rp)
{
	int c = 0;
	for (int i = lp.x; i <= rp.x; i++)
		for (int j = lp.y; j <= rp.y; j++)
			if (this->map[i][j]->get_symbol() == GROUND_SYMBOL) c++;
	int num = rand() % c + 1;
	c = 0;
	for (int i = lp.x; i <= rp.x; i++)
		for (int j = lp.y; j <= rp.y; j++)
		{
			if (this->map[i][j]->get_symbol() == GROUND_SYMBOL) c++;
			if (c == num) return this->map[i][j]->get_point();
		}
};

void Map::addActor(char c, Point p)
{
	 switch(c)
	 {
	 	case ZOMBIE_SYMBOL:
			this->actors.push_back(new Zombie(4, 2, p)); break;
	 	case DRAGON_SYMBOL:
			this->actors.push_back(new Dragon(70, 25, p)); break;
		case BONUS_MEDKIT_COLOR:
			this->actors.push_back(new Medkit(1, bonus_health_value, p)); break;
	 }
	 this->changeActor(this->actors[this->actors.size() - 1]);
};

void Map::changeActor(Actor *actor)
{
	Point p = actor->get_point();
	delete this->map[p.x][p.y];
	this->map[p.x][p.y] = actor;
};

void Map::printMap(WINDOW *win)
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			wattron(win, COLOR_PAIR(this->map[i][j]->get_color()));
			mvwprintw(win, i, j, "%c", this->map[i][j]->get_symbol());
		}
	}
	wattron(win, COLOR_PAIR(BASE_COLOR));
};
