#include "units.h"
#include "gamemanager.h"
#include <unistd.h>

Point Actor::get_point()
{
	return this->point;
}

void Actor::set_point(int x, int y)
{
	this->point.x = x;
	this->point.y = y;
}

void Actor::set_point(Point p)
{
	this->point = p;
}

int Actor::get_hp()
{
	return this->health;
}

void Actor::set_hp(int value)
{
	this->health = value;
}

bool Actor::is_die()
{
	return this->get_hp() > 0 ? false : true;
}

int Character::get_damage()
{
	return this->damage;
}

void Character::move(Map &m, Point p)
{
	//this->collide(m.map[this->getY() + y][this->getX() + x]);
}

void Knight::collide(Actor* actor)
{
	actor->collide(this);
};

void Knight::collide(Monster *monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
};

void Knight::collide(Ground *ground)
{
	this->set_hp(this->get_hp() - 1);
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

void Ground::collide(Actor *actor)
{
	actor->collide(this);
}

void Ground::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
}

void Ground::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
}

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
	mvprintw(1, 1, "YOU WIN!");
	sleep(1);
	exit(0);
};

char Princess::get_symbol()
{
	return PRINCESS_SYMBOL;
};

int Princess::get_color()
{
	return PRINCESS_COLOR;
};
