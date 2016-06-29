#pragma once
#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "point.h"
#include "config.h"
#include "map.h"

class Actor
{
protected:
	int health;
	Point point;
public:
	Actor() : health(0) { point.x = point.y = 0; };
	Actor(int h, Point p) : health(h) { point = p; };
	virtual ~Actor() { };
	Point get_point();
	void set_point(int x, int y);
	void set_point(Point p);
	int get_hp();
	virtual void set_hp(int value) { this->health = value; };
	bool is_die();
	virtual int get_color() { };
	virtual char get_symbol() { };
	virtual Point get_direction(Map& map) { };
	virtual Point get_direction() { };
	virtual void specialSkill(Map& map) { };
	virtual void action(Map& map) { };
	virtual void collide(Actor* actor) = 0;
    virtual void collide(Character* character) { };
    virtual void collide(Knight* knight) { };
    virtual void collide(Princess* princess) { };
    virtual void collide(Monster* monster) { };
	virtual void collide(Spawn* spawn) { };
	virtual void collide(Ground* ground) { };
	virtual void collide(Wall* wall) { };
	virtual void collide(Medkit* medkit) { };
	virtual void collide(Fireball* fireball) { };
};

class Character: public Actor
{
protected:
	int damage;
	int max_hp;
public:
	Character() : damage(0), Actor(0, Point()) { };
	Character(int h, int d, Point p) : damage(d), Actor(h, p) { };
	int get_damage();
};

class Knight: public Character
{
public:
	Knight() { };
	Knight(int h, int d, Point p) : Character(h, d, p) { };
	int get_color();
	char get_symbol();
	void set_hp(int value);
	void collide(Actor* actor);
	void collide(Knight* knight) { };
	void collide(Monster *monster);
	void collide(Fireball* fireball);
};

class Princess: public Character
{
public:
	Princess() { };
	Princess(int h, int d, Point p) : Character(h, d, p) { };
	char get_symbol();
	int get_color();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Fireball* fireball);
	void collide(Princess* princess) { };
};

class Monster: public Character
{
public:
	Monster() { };
	Monster(int h, int d, Point p) : Character(h, d, p) { };
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster *monster) {};
	void collide(Princess* princess);
	void collide(Fireball* fireball);
	Point get_direction(Map& map);
};

class Fireball: public Character
{
private:
	Point direction;
public:
	Fireball() { };
	Fireball(int h, int d, Point p, Point dir) : direction(dir),
												 Character(h, d, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster* monster);
	void collide(Fireball* fireball) { };
	Point get_direction();
	Point get_direction(Map& map);
};

class Zombie: public Monster
{
public:
	Zombie() { };
	Zombie(int h, int d, Point p) : Monster(h, d, p) { };
	int get_color();
	char get_symbol();
	void set_hp(int value);
};

class Dragon: public Monster
{
public:
	Dragon() { };
	Dragon(int h, int d, Point p) : Monster(h, d, p) { };
	int get_color();
	char get_symbol();
	void set_hp(int value);
};

class Wizard: public Monster
{
public:
	Wizard() { };
	Wizard(int h, int d, Point p) : Monster(h, d, p) { };
	int get_color();
	char get_symbol();
	void set_hp(int value);
	void specialSkill(Map& map);
};

class Environment: public Actor
{
public:
	Environment() : Actor(0, Point()) { };
	Environment(int h, Point p) : Actor(h, p) { };
};

class Wall: public Environment
{
public:
	Wall() : Environment(0, Point()) { };
	Wall(int h, Point p) : Environment(h, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight) { };
	void collide(Monster* monster) { };
	void collide(Wall* wall) { };
	void collide(Fireball* fireball);
};

class Ground: public Environment
{
public:
	Ground() : Environment(0, Point()) { };
	Ground(int h, Point p) : Environment(h, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster* monster);
	void collide(Fireball* fireball);
	void collide(Environment* environment) { };
};

class Spawn: public Actor
{
protected:
    int timer = 0;
public:
    Spawn() : Actor(0, Point()) {};
    Spawn(int h, int t, Point p) : timer(t), Actor(h, p) { };
	void collide(Actor* actor) { };
	void collide(Knight* knight) { };
	void collide(Monster* monster) { };
	void collide(Fireball* fireball) { };
};

class SpawnMedkit: public Spawn
{
public:
    SpawnMedkit() : Spawn(0, 0, Point()) { };
    SpawnMedkit(int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
};

class SpawnZombies: public Spawn
{
public:
    SpawnZombies() : Spawn(0, 0, Point()) { };
    SpawnZombies(int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
	int get_color();
	char get_symbol();
};

class SpawnMedkits: public Spawn
{
public:
	SpawnMedkits() : Spawn(0, 0, Point()) { };
    SpawnMedkits(int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
};

class SpawnDragons: public Spawn
{
public:
    SpawnDragons() : Spawn(0, 0, Point()) { };
    SpawnDragons(int h, int t, Point p) : Spawn(h, t, p) { };
	void action(Map& map);
	int get_color();
	char get_symbol();
};

class Object: public Actor
{
private:
	int value_smth;
public:
	Object() : value_smth(0), Actor(0, Point()) { };
	Object(int h, int v, Point p) : value_smth(v), Actor(h, p) { };
	int get_value_smth();
};

class Medkit: public Object
{
public:
	Medkit() { };
	Medkit(int h, int v, Point p) : Object(h, v, p) { };
	int get_color();
	char get_symbol();
	void collide(Actor* actor);
	void collide(Knight* knight);
	void collide(Monster* monster);
	void collide(Fireball* fireball);
	void collide(Medkit* medkit) { };
};
