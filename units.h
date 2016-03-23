#pragma once
#include "map.h"

class BaseCharacter
{
public:
	virtual void collide(class Character* ch) = 0;
	virtual void collide(class Knight* ch) = 0;
	virtual void collide(class Monster* ch) = 0;
};

class Character: public BaseCharacter
{
protected:
	int health, damag, x, y;
public:
	Character (int h, int d, int x, int y) : health(h), damag(d), x(x), y(y) {};
	virtual void move(Map &m, int x, int y) {};
	virtual int hitPoints();
	virtual int damage();
	void collide(class Character* ch) {};
	void collide(class Knight* ch) {};
	void collide(class Monster* ch) {};
	int getX();
	int getY();
	void setCoordinates(int x, int y);
};

class Knight: public Character
{
public:
	Knight (int h = 1, int d = 0, int i = 0, int j = 0) : Character (h, d, i, j) {};
	void move(Map &m, int x, int y);
	void collide(class Monster* ch) {};
};

class Princess: public Character
{
public:
	Princess (int h = 1, int d = 0, int i = 0, int j = 0) : Character (h, d, i, j) {};
};

class Monster: public Character
{
public:
	Monster (int h = 1, int d = 0, int i = 0, int j = 0) : Character (h, d, i, j) {};
	void move(Map &m, int x, int y);
};

class Zombie: public Monster
{
public:
	Zombie (int h = 3, int d = 0, int i = 0, int j = 0) : Monster (h, d, i, j) {};
};

class Dragon: public Monster
{
public:
	Dragon (int h = 20, int d = 0, int i = 0, int j = 0) : Monster (h, d, i, j) {};
};