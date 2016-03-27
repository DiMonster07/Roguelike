#include "units.h"
#include <iostream>
#include <fstream>

int Character::hitPoints()
{
	return this->health;
}

int Character::get_damage()
{
	return this->damage;
}

void Character::set_hp(int value)
{
	this->health = value;
}

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

void Monster::move(Map &m, int x, int y)
{
	if (m.map[this->y + y][this->x + x] == '.')
	{
		m.map[this->y][this->x] = '.';
		m.map[this->y + y][this->x + x] = 'Z';		
		this->x += x;
		this->y += y;
	}
}

void Knight::move(Map &m, int x, int y)
{
	if (m.map[this->y + y][this->x + x] == '.')
	{
		m.map[this->y][this->x] = '.';
		m.map[this->y + y][this->x + x] = 'K';
		this->x += x;
		this->y += y;
	}
}