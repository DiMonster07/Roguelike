#include "units.h"
#include "gamemanager.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

int Character::get_hp()
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

void Character::move(Map &m, int x, int y)
{
	if (m.map[this->y + y][this->x + x] == '.')
	{
		m.map[this->y][this->x] = '.';
		m.map[this->y + y][this->x + x] = this->get_symbol();
		this->x += x;
		this->y += y;
	}
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

char Knight::get_symbol() 
{ 
	return KNIGHT_SYMBOL;
};

void Princess::collide(Actor* actor) 
{ 
	actor->collide(this); 
};

char Princess::get_symbol() 
{ 
	return PRINCESS_SYMBOL;
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

char Dragon::get_symbol() 
{ 
	return DRAGON_SYMBOL;
};