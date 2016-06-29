#pragma once
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include "point.h"
#include "json_importer.h"
#include "meta.h"

class Config
{
public:
    Config() { };
	static Config& instance();
	void parse(char* file_name);
	void setVariables();
	char get_knight_symbol() { return KNIGHT_SYMBOL; }
	char get_princess_symbol() { return PRINCESS_SYMBOL; }
	char get_zombie_symbol() { return ZOMBIE_SYMBOL; }
	char get_dragon_symbol() { return DRAGON_SYMBOL; }
    char get_wizard_symbol() { return WIZARD_SYMBOL; }
	char get_zombies_spawn_symbol() { return ZOMBIES_SPAWN_SYMBOL; }
	char get_dragons_spawn_symbol() { return DRAGONS_SPAWN_SYMBOL; }
	char get_wall_symbol() { return WALL_SYMBOL; }
	char get_ground_symbol() { return GROUND_SYMBOL; }
	char get_medkit_symbol() { return MEDKIT_SYMBOL; }

	int get_knight_hp() { return knight_health; }
    int get_knight_max_hp() { return knight_max_health; }
	int get_zombie_hp() { return zombie_health; }
    int get_zombie_max_hp() { return zombie_max_health; }
	int get_dragon_hp() { return dragon_health; }
    int get_dragon_max_hp() { return dragon_max_health; }
	int get_wizard_hp() { return wizard_health; }
    int get_wizard_max_hp() { return wizard_max_health; }
	int get_princess_hp() { return princess_health; }

	int get_knight_damage() { return knight_damage; }
	int get_zombie_damage() { return zombie_damage; }
	int get_dragon_damage() { return dragon_damage; }
	int get_fireball_damage(){ return fireball_damage; }
	int get_wizard_damage() { return wizard_damage; }

    int get_medkit_timer() { return medkit_spawn_timer; }
	int get_zombies_spawn_timer() { return zombies_spawn_timer; }
	int get_dragons_spawn_timer() { return dragons_spawn_timer; }
	int get_medkit_max_count() { return medkit_max_count; }
	int get_medkit_heal_power() { return medkit_heal_power; }
	~Config();
private:
	Json_importer* importer;
    char
    	GROUND_SYMBOL,
    	WALL_SYMBOL,
    	KNIGHT_SYMBOL,
    	PRINCESS_SYMBOL,
    	ZOMBIE_SYMBOL,
    	DRAGON_SYMBOL,
    	WIZARD_SYMBOL,
    	MEDKIT_SYMBOL,
    	DRAGONS_SPAWN_SYMBOL,
    	ZOMBIES_SPAWN_SYMBOL;
    int
    	knight_health,
    	knight_damage,
        knight_max_health,
    	princess_health,
    	medkit_heal_power,
    	medkit_max_count,
    	medkit_spawn_timer,
    	dragons_spawn_timer,
    	zombies_spawn_timer,
    	wizard_timer,
    	wizard_damage,
    	wizard_health,
        wizard_max_health,
    	zombie_health,
    	zombie_damage,
        zombie_max_health,
    	dragon_health,
        dragon_max_health,
    	dragon_damage,
    	fireball_damage;
};
