#include "units.h"
#include <iostream>
#include <fstream>

int Character::hitPoints()
{
	return this->health;
}

int Character::damage()
{
	return this->damag;
}

int Character::getX()
{
	return this->x;
}

int Character::getY()
{
	return this->y;
}

void Character::setCoordinates(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Knight::move(Map &m, courseX x, courseY y)
{
	if (m.map[this->y + y][this->x + x] == '.')
	{
		m.map[this->y][this->x] = '.';
		m.map[this->y + y][this->x + x] = 'K';		
		this->x += x;
		this->y += y;
	}
}