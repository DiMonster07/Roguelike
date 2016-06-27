#include "map.h"
#include "gamemanager.h"
#include "units.h"
#include <malloc.h>
#include <fstream>
#include <iostream>

Map::Map(std::string name_map)
{
	std::ifstream input(DEFAULT_DIR + name_map);
	char c;
	input >> this->rows >> this->cols;
	for (int i = 0; i < this->rows; i++)
	{
		std::vector<Actor*> row;
		for (int j = 0; j < this->cols; j++)
		{
			Actor* new_actor;
			Wizard* wizard;
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
				case KNIGHT_SYMBOL:
					this->knight = new Knight(knight_health, knight_damage,
												  Point(i, j));
					row.push_back(this->knight);
					break;
				case PRINCESS_SYMBOL:
					this->princess = new Princess(princess_health, princess_damage,
												  Point(i, j));
					row.push_back(this->princess);
					break;
				case ZOMBIE_SYMBOL:
					new_actor = new Zombie(zombie_health, zombie_damage, Point(i, j));
					row.push_back(new_actor);
					break;
				case DRAGON_SYMBOL:
					new_actor = new Dragon(dragon_health, dragon_damage,
										   	 	  Point(i, j));
					row.push_back(new_actor);
					break;
				case WIZARD_SYMBOL:
					this->wizard = new Wizard(wizard_health, wizard_damage,
										   		  Point(i, j));
					row.push_back(this->wizard);
					break;
				case MEDKIT_SYMBOL:
					new_actor = new Medkit(medkit_health, bonus_health_value,
										   		  Point(i, j));
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

Point Map::findFreePlace()
{
	int c = 0;
	Point lp(1, 1); Point rp(this->rows - 2, this->cols - 2);
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

Point Map::get_right_ang()
{
	return Point(this->cols - 2, this->rows - 2);
};

void Map::addActor(char c, Point p)
{
	 switch(c)
	 {
	 	case ZOMBIE_SYMBOL:
			this->actors.push_back(new Zombie(zombie_health, zombie_damage, p));
																	  break;
	 	case DRAGON_SYMBOL:
			this->actors.push_back(new Dragon(dragon_health, dragon_damage, p));
																	  break;
		case MEDKIT_COLOR:
			this->actors.push_back(new Medkit(medkit_health, bonus_health_value, p));
																	  break;
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
