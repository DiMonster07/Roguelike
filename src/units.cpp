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

bool Actor::is_die()
{
	return this->get_hp() > 0 ? false : true;
};

int Character::get_damage()
{
	return this->damage;
};

void Knight::set_hp(int value)
{
	if (value > Config::instance().get_knight_max_hp())
		this->health = Config::instance().get_knight_max_hp();
	else
		this->health = value;
};

void Knight::collide(Actor* actor)
{
	actor->collide(this);
};

void Knight::collide(Monster *monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
};

void Knight::collide(Fireball* fireball)
{
	this->set_hp(this->get_hp() - fireball->get_damage());
	fireball->set_hp(-1);
};

char Knight::get_symbol()
{
	return Config::instance().get_knight_symbol();
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

void Monster::collide(Fireball* fireball)
{
	this->set_hp(this->get_hp() - fireball->get_damage());
	fireball->set_hp(-1);
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

void Fireball::collide(Actor* actor)
{
	actor->collide(this);
};

void Fireball::collide(Knight* knight)
{
	this->set_hp(-1);
	knight->set_hp(knight->get_hp() - this->get_damage());
};

void Fireball::collide(Monster* monster)
{
	this->set_hp(-1);
	monster->set_hp(monster->get_hp() - this->get_damage());
};

Point Fireball::get_direction()
{
	return this->direction;
};

Point Fireball::get_direction(Map& map)
{
	return this->direction;
};

char Fireball::get_symbol()
{
	return FIREBALL_DIR_SYMBOL[this->get_direction()];
};

int Fireball::get_color()
{
	return FIREBALL_COLOR;
};

void Zombie::set_hp(int value)
{
	if (value > Config::instance().get_zombie_max_hp())
		this->health = Config::instance().get_zombie_max_hp();
	else
		this->health = value;
};

char Zombie::get_symbol()
{
	return Config::instance().get_zombie_symbol();
};

int Zombie::get_color()
{
	return ZOMBIE_COLOR;
};

void Dragon::set_hp(int value)
{
	if (value > Config::instance().get_dragon_max_hp())
		this->health = Config::instance().get_dragon_max_hp();
	else
		this->health = value;
};

char Dragon::get_symbol()
{
	return Config::instance().get_dragon_symbol();
};

int Dragon::get_color()
{
	return DRAGON_COLOR;
};


void Wizard::set_hp(int value)
{
	if (value > Config::instance().get_wizard_max_hp())
		this->health = Config::instance().get_wizard_max_hp();
	else
		this->health = value;
};

void Wizard::specialSkill(Map& map)
{
	Point wpoint = this->get_point();
	Point kpoint = map.knight->get_point();
	if (wpoint.x == kpoint.x || wpoint.y == kpoint.y)
	{
		Point dir;
		if (wpoint.x == kpoint.x)
			dir = Point(0, (wpoint.y > kpoint.y ? -1 : 1));
		else if (wpoint.y == kpoint.y)
			dir = Point((wpoint.x > kpoint.x ? -1 : 1), 0);
		wpoint = wpoint + dir;
		if (map.isActorTypeInPlace(Config::instance().get_ground_symbol(), wpoint))
	 		map.addActor(new Fireball(1,
									  Config::instance().get_fireball_damage(),
									  wpoint, dir));
	}
};

char Wizard::get_symbol()
{
	return Config::instance().get_wizard_symbol();
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

void Ground::collide(Fireball* fireball)
{
	this->set_hp(this->get_hp() - fireball->get_damage());
};

char Ground::get_symbol()
{
	return Config::instance().get_ground_symbol();
};

int Ground::get_color()
{
	return GROUND_COLOR;
};

void Wall::collide(Actor* actor)
{
	actor->collide(this);
};

void Wall::collide(Fireball* fireball)
{
	fireball->set_hp(-1);
};

char Wall::get_symbol()
{
	return Config::instance().get_wall_symbol();
};

int Wall::get_color()
{
	return WALL_COLOR;
};

void Princess::collide(Actor* actor)
{
	actor->collide(this);
};

void Princess::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
};

void Princess::collide(Fireball* fireball)
{
	this->set_hp(this->get_hp() - fireball->get_damage());
	fireball->set_hp(-1);
};

char Princess::get_symbol()
{
	return Config::instance().get_princess_symbol();
};

int Princess::get_color()
{
	return PRINCESS_COLOR;
};

int Object::get_value_smth()
{
	return this->value_smth;
};

void Medkit::collide(Actor *actor)
{
	actor->collide(this);
};

void Medkit::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
	knight->set_hp(knight->get_hp() + this->get_value_smth());
};

void Medkit::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
	monster->set_hp(monster->get_hp() + this->get_value_smth());
};

void Medkit::collide(Fireball* fireball)
{
	fireball->set_hp(-1);
};

char Medkit::get_symbol()
{
	return Config::instance().get_medkit_symbol();
};

int Medkit::get_color()
{
	return MEDKIT_COLOR;
};

void SpawnZombies::action(Map& map)
{
	Point my_p = this->get_point();
	if (this->timer-- == 0)
	{
		Point p = map.findFreePlace(my_p - spawn_range, my_p + spawn_range);
		map.addActor(Config::instance().get_zombie_symbol(), p);
		this->timer = Config::instance().get_zombies_spawn_timer();
	}
};

char SpawnZombies::get_symbol()
{
    return Config::instance().get_zombies_spawn_symbol();
};

int SpawnZombies::get_color()
{
    return ZOMBIES_SPAWN_COLOR;
};

void SpawnMedkit::action(Map& map)
{
	Point my_p = this->get_point();
	if (this->timer-- == 0)
	{
		if (map.getActorsCount(Config::instance().get_medkit_symbol()) <
			Config::instance().get_medkit_max_count())
		{
			Point p = map.findFreePlace();
			map.addActor(Config::instance().get_medkit_symbol(), p);
		}
		this->timer = Config::instance().get_medkit_timer();
	}
};

void SpawnDragons::action(Map& map)
{
	Point my_p = this->get_point();
	if (this->timer-- == 0)
	{
		Point p = map.findFreePlace(my_p - spawn_range, my_p + spawn_range);
		map.addActor(Config::instance().get_dragon_symbol(), p);
		this->timer = Config::instance().get_dragons_spawn_timer();
	}
};

char SpawnDragons::get_symbol()
{
    return Config::instance().get_dragons_spawn_symbol();
};

int SpawnDragons::get_color()
{
    return DRAGONS_SPAWN_COLOR;
};
