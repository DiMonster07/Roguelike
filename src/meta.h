#pragma once
#include "point.h"
#include <map>
#include <set>
#include <ncurses.h>
#include <panel.h>

#define GROUND_SYMBOL '.'
#define WALL_SYMBOL '#'
#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'
#define WIZARD_SYMBOL 'W'
#define MEDKIT_SYMBOL '+'
#define DRAGONS_SPAWN_SYMBOL '@'
#define ZOMBIES_SPAWN_SYMBOL '%'
#define CURSOR std::string(" <-")

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define UNITS_COUNT 10

#define DEFAULT_DIR std::string("../src/maps/")
#define DEFAULT_MAP_NAME std::string("1.map")
#define MAP_EXTENSION std::string(".map")

#define KEY_N 'n'
#define KEY_W 'w'
#define KEY_S 's'
#define ROWS_DEFAULT 30
#define COLS_DEFAULT 60
#define INFO_WIN_WIDTH 20

#define KEY_SPACE ' '
#define KEY_ENTER1 10

#define LEFT_ANG Point(1, 1)

#define UP_DIRECTION Point(0, -1)
#define DOWN_DIRECTION Point(0, 1)
#define LEFT_DIRECTION Point(-1, 0)
#define RIGHT_DIRECTION Point(1, 0)

#define GAME_CONTINUE 0
#define GAME_LOSE 1
#define GAME_WIN 2

#define GAME_EXIT '0'
#define GAME_START '1'
#define CREATE_MAP '2'

const int vis_range = 3;
const int att_range = 1;
const int spawn_range = 10;
const int medkit_max_count = 5;
const int medkit_spawn_timer = 5;
const int dragon_spawn_timer = 20;
const int zombies_spawn_timer = 10;
const int knight_health = 3000000;
const int knight_damage = 5;
const int wizard_timer = 3;
const int wizard_damage = 2;
const int wizard_health = 70;
const int zombie_health = 8;
const int zombie_damage = 4;
const int dragon_health = 70;
const int dragon_damage = 25;
const int princess_health = 1;
const int princess_damage = 0;
const int medkit_health = 1;
const int medkit_heal_power = 10;
const int fireball_health = 1;
const int fireball_damage = 10;

class Map;
class Actor;
class Character;
class Knight;
class Princess;
class Dragon;
class Monster;
class Zombie;
class Environment;
class Wall;
class Ground;
class Spawn;
class SpawnDragons;
class SpawnZombies;
class SpawnMedkits;
class Object;
class Medkit;
class Wizard;
class Fireball;

static std::map<Point, char> FIREBALL_DIR_SYMBOL =
{
	{ UP_DIRECTION,    '^' },
	{ DOWN_DIRECTION,  'v' },
	{ LEFT_DIRECTION,  '<' },
	{ RIGHT_DIRECTION, '>' }
};

static char units_symbols[UNITS_COUNT] =
	{ '#', '.', 'K', 'P', 'Z', 'D', '@', '%' , '+', 'W' };

static std::map<char, std::string> units_name =
{
	{ GROUND_SYMBOL, std::string("Ground") },
	{ WALL_SYMBOL, std::string("Wall") },
	{ KNIGHT_SYMBOL, std::string("Knight") },
	{ PRINCESS_SYMBOL, std::string("Princess") },
	{ ZOMBIE_SYMBOL, std::string("Zombie") },
	{ DRAGON_SYMBOL, std::string("Dragon") },
	{ DRAGONS_SPAWN_SYMBOL, std::string("Dragons spawn") },
	{ ZOMBIES_SPAWN_SYMBOL, std::string("Zombies spawn") },
	{ MEDKIT_SYMBOL, std::string("Medkit") },
	{ WIZARD_SYMBOL, std::string("Wizard") },
};

enum COLORS_UNITS
{
	WALL_COLOR = 1,
	GROUND_COLOR = 2,
	KNIGHT_COLOR = 3,
	PRINCESS_COLOR = 4,
	ZOMBIE_COLOR = 5,
	DRAGON_COLOR = 6,
	ZOMBIES_SPAWN_COLOR = 7,
	DRAGONS_SPAWN_COLOR = 8,
	WIZARD_COLOR = 9,
	MEDKIT_COLOR = 10,
	FIREBALL_COLOR = 11,
	BASE_COLOR = 12
};

static std::map<char, int> units_color =
{
	{ WALL_SYMBOL, WALL_COLOR },
	{ GROUND_SYMBOL, GROUND_COLOR },
	{ KNIGHT_SYMBOL, KNIGHT_COLOR },
	{ PRINCESS_SYMBOL, PRINCESS_COLOR },
	{ ZOMBIE_SYMBOL, ZOMBIE_COLOR },
	{ DRAGON_SYMBOL, DRAGON_COLOR },
	{ ZOMBIES_SPAWN_SYMBOL, ZOMBIES_SPAWN_COLOR },
	{ DRAGONS_SPAWN_SYMBOL, DRAGONS_SPAWN_COLOR },
	{ MEDKIT_SYMBOL, MEDKIT_COLOR },
	{ WIZARD_SYMBOL, WIZARD_COLOR }
};
