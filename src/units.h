#pragma once
#include "map.h"
#include <ncurses.h>
#include <panel.h>
#include <vector>

#define GROUND_SYMBOL '.'
#define WALL_SYMBOL '#'
#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'

class Actor
{
protected:
	int x, y;
public:
	Actor () : x(0), y(0) {};
	Actor (int x, int y) : x(x), y(y) {};
	virtual ~Actor() {};
	int getX();
	int getY();
	void setCoordinates(int x, int y);
	virtual char get_symbol() {};
	virtual int get_color() {};
	virtual void move(Map &m, int x, int y) = 0;
	virtual void collide(Actor* actor) = 0;
    virtual void collide(Character* character) {};
    virtual void collide(Knight* knight) {};
    virtual void collide(Princess* princess) {};
    virtual void collide(Monster* monster) {};
	virtual void collide(Ground* ground) {};
	virtual void collide(Wall* wall) {};
};

class Character: public Actor
{
protected:
	int health, damage;
public:
	Character () : health(0), damage(0), Actor (0, 0) {};
	Character (int h, int d, int x, int y) : health(h), damage(d),
		Actor (x, y) {};
	void move(Map &m, int x, int y);
	int get_hp();
	int get_damage();
	void set_hp(int value);
};

class Knight: public Character
{
public:
	Knight () {};
	Knight (int h, int d, int x, int y) : Character (h, d, x, y) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight) {};
	void collide(Monster *monster);
	void collide(Princess* princess);
	void collide(Ground* ground);
};

class Princess: public Character
{
public:
	Princess () {};
	Princess (int h, int d, int x, int y) : Character (h, d, x, y) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight) {};
	void collide(Princess* princess) {};
};

class Monster: public Character
{
public:
	Monster () {};
	Monster (int h, int d, int x, int y) : Character (h, d, x, y) {};
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster *monster) {};
	void collide(Princess* princess);
};

class Zombie: public Monster
{
public:
	Zombie () {};
	Zombie (int h, int d, int x, int y) : Monster (h, d, x, y) {};
	char get_symbol();
	int get_color();
};

class Dragon: public Monster
{
public:
	Dragon () {};
	Dragon (int h, int d, int x, int y) : Monster (h, d, x, y) {};
	char get_symbol();
	int get_color();
};

class Environment: public Actor
{
public:
	Environment () : Actor(0, 0) {};
	Environment (int i, int j) : Actor(i, j) {};
	void move(Map &m, int x, int y) {};
};

class Wall: public Environment
{
public:
	Wall () : Environment(0, 0) {};
	Wall (int i, int j) : Environment(i, j) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
};

class Ground: public Environment
{
private:
	int health;
public:
	Ground () : health(0), Environment(0, 0) {};
	Ground (int i, int j, int h) : health(h), Environment(i, j) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Ground* ground) {};
};
