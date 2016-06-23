#include "units.h"
#include <unistd.h>

Point Actor::get_point()
{
	return this->point;
};

void Actor::set_point(int x, int y)
{
	this->point.x = x;
	this->point.y = y;
};

void Actor::set_point(Point p)
{
	this->point = p;
};

int Actor::get_hp()
{
	return this->health;
};

void Actor::set_hp(int value)
{
	this->health = value;
};

bool Actor::is_die()
{
	return this->get_hp() > 0 ? false : true;
};

int Object::get_value()
{
	return this->value;
};

void Fireball::collide(Actor* actor)
{
	actor->collide(this);
};

void Fireball::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
	knight->set_hp(knight->get_hp() - this->get_value());
};

void Fireball::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
	monster->set_hp(monster->get_hp() - this->get_value());
};

void Fireball::collide(Wizard* wizard)
{
	this->set_hp(this->get_hp() - wizard->get_damage());
	wizard->set_hp(wizard->get_hp() - this->get_value());
};

Point Fireball::get_direction()
{
	return this->direction;
};

Point Fireball::get_direction(Map& map)
{
	return this->direction;
};

int Fireball::get_color()
{
	return FIREBALL_COLOR;
};

char Fireball::get_symbol()
{
	return FIREBALL_DIR_SYMBOL[this->get_direction()];
};

void Medkit::collide(Actor* actor)
{
	actor->collide(this);
};

void Medkit::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
	knight->set_hp(knight->get_hp() + this->get_value());
};

void Medkit::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
	monster->set_hp(monster->get_hp() + this->get_value());
};

void Medkit::collide(Wizard* wizard)
{
	this->set_hp(this->get_hp() - wizard->get_damage());
	wizard->set_hp(wizard->get_hp() + this->get_value());
};

int Medkit::get_color()
{
	return BONUS_MEDKIT_COLOR;
};

char Medkit::get_symbol()
{
	return BONUS_MEDKIT_SYMBOL;
};

int Character::get_damage()
{
	return this->damage;
};

void Knight::collide(Actor* actor)
{
	actor->collide(this);
};

void Knight::collide(Monster *monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
};

void Knight::collide(Wizard *wizard)
{
	this->set_hp(this->get_hp() - wizard->get_damage());
};

char Knight::get_symbol()
{
	return KNIGHT_SYMBOL;
};

int Knight::get_color()
{
	return KNIGHT_COLOR;
};

void Monster::collide(Actor* actor)
{
	actor->collide(this);
};

void Monster::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
};

void Monster::collide(Princess *princess)
{
	mvprintw(1, 1, "YOU LOSE!");
	sleep(1);
	exit(0);
};

Point Monster::get_direction(Map& map)
{
	Point p_knight = map.knight->get_point();
	Point offset = this->get_point();
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
	return offset;
};

char Zombie::get_symbol()
{
	return ZOMBIE_SYMBOL;
};

int Zombie::get_color()
{
	return ZOMBIE_COLOR;
};

char Dragon::get_symbol()
{
	return DRAGON_SYMBOL;
};

int Dragon::get_color()
{
	return DRAGON_COLOR;
};

void Wizard::action(Map& map)
{
	Point dir = this->get_direction(map);
	this->createFireball(map, dir);
};

void Wizard::createFireball(Map& map, Point direction)
{

};

char Wizard::get_symbol()
{
	return WIZARD_SYMBOL;
};

int Wizard::get_color()
{
	return WIZARD_COLOR;
};

void Ground::collide(Actor *actor)
{
	actor->collide(this);
};

void Ground::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
};

void Ground::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
};

char Wall::get_symbol()
{
	return WALL_SYMBOL;
};

int Wall::get_color()
{
	return WALL_COLOR;
};

char Ground::get_symbol()
{
	return GROUND_SYMBOL;
};

int Ground::get_color()
{
	return GROUND_COLOR;
};

void Princess::collide(Actor* actor)
{
	actor->collide(this);
};

void Princess::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
};

char Princess::get_symbol()
{
	return PRINCESS_SYMBOL;
};

int Princess::get_color()
{
	return PRINCESS_COLOR;
};

void Spawn::dec()
{
	this->count--;
};

int Spawn::get_count()
{
	return this->count;
};

void SpawnHealth::action(Map& map)
{
	if(this->timer-- == 0)
	{
		if(this->count < 5)
		{
			this->count++;
			Point p = map.findFreePlace(LEFT_ANG, RIGHT_ANG);
			map.addActor(BONUS_MEDKIT_SYMBOL, p);
		}
		this->timer = health_spawn_timer;
	}
};

void SpawnZombies::action(Map& map)
{
	Point my_p = this->get_point();
	if (this->timer-- == 0)
	{
		Point p = map.findFreePlace(my_p - spawn_range, my_p + spawn_range);
		map.addActor(ZOMBIE_SYMBOL, p);
		this->timer = zombies_spawn_timer;
	}
};

char SpawnZombies::get_symbol()
{
    return ZOMBIES_SPAWN_SYMBOL;
};

int SpawnZombies::get_color()
{
    return ZOMBIES_SPAWN_COLOR;
};

void SpawnDragons::action(Map& map)
{
	Point my_p = this->get_point();
	if (this->timer-- == 0)
	{
		Point p = map.findFreePlace(my_p - spawn_range, my_p + spawn_range);
		map.addActor(DRAGON_SYMBOL, p);
		this->timer = dragon_spawn_timer;
	}
};

char SpawnDragons::get_symbol()
{
    return DRAGONS_SPAWN_SYMBOL;
};

int SpawnDragons::get_color()
{
    return DRAGONS_SPAWN_COLOR;
};
