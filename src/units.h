#pragma once
#include "map.h"
#include "point.h"
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
	int health;
	Point point;
public:
	Actor () : health(0) { point.x = point.y = 0; };
	Actor (int h, int x, int y) : health(h) { point.x = x; point.y = y; };
	virtual ~Actor() {};
	Point get_point();
	void set_point(int x, int y);
	void set_point(Point p);
	int get_hp();
	void set_hp(int value);
	bool is_die();
	virtual char get_symbol() {};
	virtual int get_color() {};
	virtual void move(Map &m, Point p) = 0;
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
	int damage;
public:
	Character () : damage(0), Actor (0, 0, 0) {};
	Character (int h, int d, int x, int y) : damage(d), Actor (h, x, y) {};
	void move(Map &m, Point p);
	int get_damage();
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
	void collide(Knight* knight);
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
	Environment () : Actor(0, 0, 0) {};
	Environment (int h, int x, int y) : Actor(h, x, y) {};
	void move(Map &m, Point p) {};
};

class Wall: public Environment
{
public:
	Wall () : Environment(0, 0, 0) {};
	Wall (int h, int x, int y) : Environment(h, x, y) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor) {};
	void collide(Knight* knight) {};
	void collide(Monster* monster) {};
};

class Ground: public Environment
{
public:
	Ground () : Environment(0, 0, 0) {};
	Ground (int h, int x, int y) : Environment(h, x, y) {};
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster* monster);
	void collide(Environment* environment) {};
};
