#pragma once
#include "map.h"
#include <ncurses.h>
#include <panel.h>
#include <vector>

class Actor;
class Character;
class Knight;
class Princess;
class Monster;

class Actor
{
protected:
	int x, y;
public:
	Actor (int x, int y) : x(x), y(y) {};
	int getX();
	int getY();
	void setCoordinates(int x, int y);
	virtual void move(Map &m, int x, int y) = 0;
	virtual void collide(Actor* actor) = 0;
    virtual void collide(Character* character) {};
    virtual void collide(Knight* knight) {};
    virtual void collide(Princess* princess) {};
    virtual void collide(Monster* monster) {};
};

class Character: public Actor
{
protected:
	int health, damage; 
public:
	Character (int h, int d, int x, int y) : health(h), damage(d), Actor (x, y) {};
	void move(Map &m, int x, int y) {};
	virtual int hitPoints();
	virtual int get_damage();
	void set_hp(int value);
	void collide(Character* character) {};
};

class Knight: public Character
{
public:
	Knight (int h, int d, int x, int y) : Character (h, d, x, y) {};
	void move(Map &m, int x, int y);
	void collide(Actor* actor) { actor->collide(this); };
	void collide(Knight* knight) {  };
	void collide(Monster *monster) {  };
};

class Princess: public Character
{
public:
	Princess (int h, int d, int x, int y) : Character (h, d, x, y) {};
	void collide(Actor* actor) { actor->collide(this); };
	void collide(Knight* knight) {};
	void collide(Monster *monster) {};
};

class Monster: public Character
{
public:
	Monster (int h, int d, int x, int y) : Character (h, d, x, y) {};
	void move(Map &m, int x, int y);
	void collide(Actor* actor) { actor->collide(this); };
	void collide(Knight* knight) 
		{ knight->set_hp(knight->hitPoints() - this->get_damage()); };
	void collide(Monster *monster) {};
};

class Zombie: public Monster
{
public:
	Zombie (int h, int d, int x, int y) : Monster (h, d, x, y) {};
};

class Dragon: public Monster
{
public:
	Dragon (int h, int d, int x, int y) : Monster (h, d, x, y) {};
};