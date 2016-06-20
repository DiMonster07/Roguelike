#pragma once
#include "point.h"
#define GROUND_SYMBOL '.'
#define WALL_SYMBOL '#'
#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'
#define DRAGONS_SPAWN_SYMBOL '@'
#define ZOMBIES_SPAWN_SYMBOL '%'
#define WIZARD_SYMBOL 'W'
#define BONUS_HEALTH_SYMBOL '+'

#define KEY_DAMAGE ' '

#define LEFT_ANG Point(1, 1)
#define RIGHT_ANG Point(28, 58)
#define UP_DIRECTION Point(-1, 0)
#define DOWN_DIRECTION Point(1, 0)
#define LEFT_DIRECTION Point(0, -1)
#define RIGHT_DIRECTION Point(0, 1)

#define GAME_WIN 2
#define GAME_LOSE 1
#define GAME_CONTINUE 0

const int vis_range = 3;
const int att_range = 1;
const int spawn_range = 10;
const int zombies_spawn_timer = 10;
const int dragon_spawn_timer = 20;
const int health_spawn_timer = 3;
const int bonus_health_value = 10;
const int knight_health = 300;

class Actor;
class Character;
class Knight;
class Princess;
class Monster;
class Wizard;
class Environment;
class Wall;
class Ground;
class Spawn;
class SpawnDragons;
class SpawnZombies;
class Health;
class Map;

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
	BONUS_HEALTH_COLOR = 10,
	BASE_COLOR = 11
};
