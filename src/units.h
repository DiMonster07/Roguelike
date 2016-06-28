#pragma once
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include <iostream>
#include "point.h"
#include "map.h"

class Actor
{
protected:
	int health;
	Point point;
public:
	Actor () : health(0) { point.x = point.y = 0; };
	Actor (int h, Point p) : health(h) { point = p; };
	virtual ~Actor() { };
	Point get_point();
	void set_point(int x, int y);
	void set_point(Point p);
	int get_hp();
	void set_hp(int value);
	bool is_die();
	virtual int get_color() { };
	virtual char get_symbol() { };
	virtual Point get_direction(Map& map) { };
	virtual void action(Map& map) { };
	virtual void collide(Actor* actor) = 0;
    virtual void collide(Character* character) { };
    virtual void collide(Knight* knight) { };
    virtual void collide(Princess* princess) { };
    virtual void collide(Monster* monster) { };
	virtual void collide(Spawn* spawn) { };
	virtual void collide(Ground* ground) { };
	virtual void collide(Medkit* medkit) { };
	virtual void collide(Wall* wall) { };
};

class Object: public Actor
{
protected:
	int value;
public:
	Object () : value(0), Actor(0, Point()) { };
	Object (int h, int v, Point p) : value(v), Actor(h, p) { };
	int get_value();
};

class Fireball: public Object
{
private:
	Point direction;
public:
	Fireball () : Object(0, 0, Point()) { };
	Fireball (int h, int v, Point p) : Object(h, v, p) { };
	int get_color();
	char get_symbol();
	Point get_direction(Map& map);
	Point get_direction();
	void collide(Actor* actor);
	void collide(Fireball* fireball) { };
	void collide(Knight* knight);
	void collide(Monster *monster);
	void collide(Wizard *wizard);
};

class Medkit: public Object
{
public:
	Medkit () : Object(0, 0, Point()) { };
	Medkit (int h, int v, Point p) : Object(h, v, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Medkit* medkit) { };
	void collide(Knight* knight);
	void collide(Monster *monster);
	void collide(Wizard *wizard);
};

class Character: public Actor
{
protected:
	int damage;
	int max_hp;
public:
	Character () : damage(0), Actor (0, Point()) { };
	Character (int h, int d, Point p) : damage(d), Actor (h, p) { };
	int get_damage();
};

class Knight: public Character
{
public:
	Knight () { };
	Knight (int h, int d, Point p) : Character (h, d, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight) { };
	void collide(Monster *monster);
	void collide(Wizard *wizard);
};

class Princess: public Character
{
public:
	Princess () { };
	Princess (int h, int d, Point p) : Character (h, d, p) { };
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Princess* princess) { };
	void collide(Wizard *wizard);
};

class Monster: public Character
{
public:
	Monster () { };
	Monster (int h, int d, Point p) : Character (h, d, p) { };
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster *monster) {};
	void collide(Princess* princess);
	Point get_direction(Map& map);
};

class Zombie: public Monster
{
public:
	Zombie () { };
	Zombie (int h, int d, Point p) : Monster (h, d, p) { };
	int get_color();
	char get_symbol();
};

class Dragon: public Monster
{
public:
	Dragon () { };
	Dragon (int h, int d, Point p) : Monster (h, d, p) { };
	int get_color();
	char get_symbol();
};

class Wizard: public Monster
{
private:
	int timer = wizard_timer;
public:
	Wizard () { };
	Wizard (int h, int d, Point p) : Monster (h, d, p) { };
	void action(Map &map);
	void createFireball(Map& map, Point direction);
	Point get_direction(Map& map);
	int get_color();
	char get_symbol();
};

class Environment: public Actor
{
public:
	Environment () : Actor(0, Point()) { };
	Environment (int h, Point p) : Actor(h, p) { };
};

class Wall: public Environment
{
public:
	Wall () : Environment(0, Point()) { };
	Wall (int h, Point p) : Environment(h, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor) { };
	void collide(Knight* knight) { };
	void collide(Monster* monster) { };
};

class Ground: public Environment
{
public:
	Ground () : Environment(0, Point()) { };
	Ground (int h, Point p) : Environment(h, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster* monster);
	void collide(Environment* environment) { };
};

class Spawn: public Actor
{
protected:
    int timer = 0;
	int count = 0;
public:
    Spawn () : Actor(0, Point()) {};
    Spawn (int h, int t, Point p) : timer(t), Actor(h, p) { };
	void dec();
	int get_count();
	void collide(Actor* actor) { };
	void collide(Knight* knight) { };
	void collide(Monster *monster) { };
};

class SpawnMedkit: public Spawn
{
public:
    SpawnMedkit () : Spawn(0, 0, Point()) { };
    SpawnMedkit (int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
};

class SpawnZombies: public Spawn
{
public:
    SpawnZombies () : Spawn(0, 0, Point()) { };
    SpawnZombies (int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
	int get_color();
	char get_symbol();
};

class SpawnDragons: public Spawn
{
public:
    SpawnDragons () : Spawn(0, 0, Point()) { };
    SpawnDragons (int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
	int get_color();
	char get_symbol();
};
