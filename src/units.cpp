#include "units.h"
#include "gamemanager.h"
#include <unistd.h>

int Actor::getX()
{
	return this->x;
}

int Actor::getY()
{
	return this->y;
}

void Actor::setCoordinates(int x, int y)
{
	this->x = x;
	this->y = y;
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

void Character::move(Map &m, int x, int y)
{
	this->collide(m.map[this->getY() + y][this->getX() + x]);
}

void Knight::collide(Actor* actor)
{
	actor->collide(this);
};

void Knight::collide(Monster *monster)
{
	monster->set_hp(monster->get_hp() - this->get_damage());
};

void Knight::collide(Princess *princess)
{
	mvprintw(1, 1, "YOU WIN!");
	sleep(1);
	exit(0);
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
	knight->set_hp(knight->get_hp() - this->get_damage());
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

void Environment::collide(Actor *actor)
{
	actor->collide(this);
}

void Environment::collide(Knight* knight)
{
	this->set_hp(this->get_hp() - knight->get_damage());
}

void Environment::collide(Monster* monster)
{
	this->set_hp(this->get_hp() - monster->get_damage());
}

// void Wall::collide(Actor* actor)
// {
// 	actor->collide(this);
// };

char Wall::get_symbol()
{
	return WALL_SYMBOL;
};

int Wall::get_color()
{
	return WALL_COLOR;
};

// void Ground::collide(Knight* knight)
// {
// 	knight->set_hp(knight->get_hp() - 1);
// }
//
// void Ground::collide(Actor* actor)
// {
// 	actor->collide(this);
// };

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

char Princess::get_symbol()
{
	return PRINCESS_SYMBOL;
};

int Princess::get_color()
{
	return PRINCESS_COLOR;
};
