#pragma once
#include "map.h"


enum courseX { LEFT = -1, NONEX = 0, RIGHT = 1 };
enum courseY { UP = -1, NONEY = 0, DOWN = 1 };

class Character 
{
protected:
	int health, damag, x, y;
public:
	Character (int h, int d, int x, int y) : health(h), damag(d), x(x), y(y) {};
	virtual void move(Map &m, courseX x, courseY y) {};
	virtual int hitPoints();
	virtual int damage();
	int getX();
	int getY();
	void setCoordinates(int x, int y);
};

class Knight: public Character
{
public:
	Knight (int h = 1, int d = 0, int i = 0, int j = 0) : Character (h, d, i, j) {};
	void move(Map &m, courseX x, courseY y);
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