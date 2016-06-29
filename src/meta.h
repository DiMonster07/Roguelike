#pragma once
#include "point.h"
#include <map>
#include <set>
#include <ncurses.h>
#include <panel.h>

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

std::map<char, int> get_units_color();
