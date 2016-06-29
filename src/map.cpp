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
			SpawnDragons* new_spawnd;
			SpawnZombies* new_spawnz;
			input >> c;
			if (c == Config::instance().get_wall_symbol())
			{
				new_actor = new Wall(3, Point(j, i));
				row.push_back(new_actor);
			} else if (c == Config::instance().get_ground_symbol())
			{
				new_actor = new Ground(1, Point(j, i));
				row.push_back(new_actor);
			} else if (c == Config::instance().get_knight_symbol())
			{
				this->knight = new Knight(Config::instance().get_knight_hp(),
										  Config::instance().get_knight_damage(),
										  Point(j, i));
				row.push_back(this->knight);
			} else if (c == Config::instance().get_princess_symbol())
			{
				this->princess = new Princess(Config::instance().get_princess_hp(),
											  0, Point(j, i));
				row.push_back(this->princess);
			} else if (c == Config::instance().get_zombie_symbol())
			{
				new_actor = new Zombie(Config::instance().get_zombie_hp(),
									   Config::instance().get_zombie_damage(),
									   Point(j, i));
				this->actors.push_back(new_actor);
				row.push_back(new_actor);
			} else if (Config::instance().get_dragon_symbol())
			{
				new_actor = new Dragon(Config::instance().get_dragon_hp(),
									   Config::instance().get_dragon_damage(),
									   Point(j, i));
				this->actors.push_back(new_actor);
				row.push_back(new_actor);
			} else if (Config::instance().get_wizard_symbol())
			{
				new_actor = new Wizard(Config::instance().get_wizard_hp(),
									   Config::instance().get_wizard_damage(),
									   Point(j, i));
				this->actors.push_back(new_actor);
				row.push_back(new_actor);
			} else if (Config::instance().get_medkit_symbol())
			{
				new_actor = new Medkit(1,
									   Config::instance().get_medkit_heal_power(),
									   Point(j, i));
				this->actors.push_back(new_actor);
				row.push_back(new_actor);
			} else if (Config::instance().get_dragons_spawn_symbol())
			{
				new_spawnd = new SpawnDragons(
										60,
										Config::instance().get_dragons_spawn_timer(),
									   	Point(j, i));
				this->spawns.push_back(new_spawnd);
				row.push_back(new_spawnd);
			} else if (Config::instance().get_zombies_spawn_symbol())
			{
				new_spawnz = new SpawnZombies(
										30,
										Config::instance().get_zombies_spawn_timer(),
									   	Point(j, i));
				this->spawns.push_back(new_spawnz);
				row.push_back(new_spawnz);
			}
		}
		map.push_back(row);
	}
};

Point Map::findFreePlace(Point lp, Point rp)
{
	int c = 0;
	lp = this->pointValidation(lp, LEFT_SIDE);
	rp = this->pointValidation(rp, RIGHT_SIDE);
	for (int i = lp.y; i <= rp.y; i++)
		for (int j = lp.x; j <= rp.x; j++)
			if (this->map[i][j]->get_symbol() ==
				Config::instance().get_ground_symbol()) c++;
	int num = rand() % c + 1;
	c = 0;
	for (int i = lp.y; i <= rp.y; i++)
		for (int j = lp.x; j <= rp.x; j++)
		{
			if (this->map[i][j]->get_symbol() ==
				Config::instance().get_ground_symbol()) c++;
			if (c == num) return this->map[i][j]->get_point();
		}
};

Point Map::pointValidation(Point p, int side)
{
	Point res;
	if(side)
	{
		res.x = (p.x > this->cols - 2 ? this->cols - 2 : p.x);
		res.y = (p.y > this->rows - 2 ? this->rows - 2 : p.y);
	} else
	{
		res.x = (p.x < 1 ? 1 : p.x);
		res.y = (p.y < 1 ? 1 : p.y);
	}
	return res;
};

Point Map::findFreePlace()
{
	int c = 0;
	Point lp(1, 1); Point rp(this->cols - 2, this->rows - 2);
	for (int i = lp.y; i <= rp.y; i++)
		for (int j = lp.x; j <= rp.x; j++)
			if (this->map[i][j]->get_symbol() ==
				Config::instance().get_ground_symbol()) c++;
	int num = rand() % c + 1;
	c = 0;
	for (int i = lp.y; i <= rp.y; i++)
		for (int j = lp.x; j <= rp.x; j++)
		{
			if (this->map[i][j]->get_symbol() ==
				Config::instance().get_ground_symbol()) c++;
			if (c == num) return this->map[i][j]->get_point();
		}
};

int Map::getActorsCount(char type_actor)
{
	int c = 0;
	for(Actor* actor: actors)
		if(actor->get_symbol() == type_actor) c++;
	return c;
};

Point Map::get_right_ang()
{
	return Point(this->cols - 2, this->rows - 2);
};

void Map::addActor(char c, Point p)
{
	Actor* actor;
	if (c == Config::instance().get_zombie_symbol())
		actor = new Zombie(Config::instance().get_zombie_hp(),
						   Config::instance().get_zombie_damage(), p);
	else if (c == Config::instance().get_dragon_symbol())
		actor = new Dragon(Config::instance().get_dragon_hp(),
						   Config::instance().get_dragon_damage(), p);
	else if (c == Config::instance().get_medkit_symbol())
		actor = new Medkit(1, Config::instance().get_medkit_heal_power(), p);
	this->addActor(actor);
};

bool Map::isActorTypeInPlace(char c, Point p)
{
	return (this->map[p.y][p.x]->get_symbol() == c);
};

void Map::addActor(Actor* actor)
{
	this->actors.push_back(actor);
	this->changeActor(actor);
};

void Map::changeActor(Actor *actor)
{
	Point p = actor->get_point();
	delete this->map[p.y][p.x];
	this->map[p.y][p.x] = actor;
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
