#pragma once
#define GROUND_SYMBOL '.'
#define WALL_SYMBOL '#'
#define KNIGHT_SYMBOL 'K'
#define PRINCESS_SYMBOL 'P'
#define ZOMBIE_SYMBOL 'Z'
#define DRAGON_SYMBOL 'D'
#define DRAGONS_SPAWN_SYMBOL '@'
#define ZOMBIES_SPAWN_SYMBOL '%'
#define WIZARD_SYMBOL 'W'

#define KEY_DAMAGE ' '

const int vis_range = 3;
const int att_range = 1;
const int spawn_range = 10;

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
	BASE_COLOR = 10
};
