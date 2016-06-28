#pragma once
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include "point.h"
#include "json_importer.h"

class Config
{
public:
    Config() { };
	static Config& instance();
	void Parse(char* file_name);
	void SetVariables();
	char get_knight_symbol() { return knight_symbol; }
	char get_princess_symbol() { return princess_symbol; }
	char get_zombie_symbol() { return zombie_symbol; }
	char get_dragon_symbol() { return dragon_symbol; }
    char get_wizard_symbol() { return wizard_symbol; }
	char get_zombies_spawn_symbol() { return zombies_spawn_symbol; }
	char get_dragons_spawn_symbol() { return dragons_spawn_symbol; }
	char get_wall_symbol() { return wall_symbol; }
	char get_ground_symbol() { return ground_symbol; }
	char get_medkit_symbol() { return medkit_symbol; }

	int get_knight_hp() { return knight_hp; }
	int get_zombie_hp() { return zombie_hp; }
	int get_dragon_hp() { return dragon_hp; }
	int get_wizard_hp() { return wizard_hp; }
	int get_princess_hp() { return princess_hp; }

	int get_knight_damage() { return knight_damage; }
	int get_zombie_damage() { return zombie_damage; }
	int get_dragon_damage() { return dragon_damage; }
	int get_fireball_damage(){ return fireball_damage; }
	int get_wizard_damage() { return wizard_damage; }

    int get_medkit_timer() { return medkit_timer; }
	int get_zombies_spawn_timer() { return zombies_spawn_timer; }
	int get_dragons_spawn_timer() { return dragons_spawn_timer; }
	int get_medkit_max_count() { return medkit_max_count; }
	int get_medkit_heal_power() { return medkit_heal_power; }
	~Config();
private:
	Json_importer* importer;
	char knight_symbol;
	char princess_symbol;
	char zombie_symbol;
	char dragon_symbol;
	char zombies_spawn_symbol;
	char dragons_spawn_symbol;
	char wizard_symbol;
	char wall_symbol;
	char ground_symbol;
	char medkit_symbol;

	int knight_hp;
	int zombie_hp;
    int princess_hp;
	int dragon_hp;
	int wizard_hp;

	int knight_damage;
	int zombie_damage;
	int dragon_damage;
	int wizard_damage;
    int fireball_damage;

    int medkit_timer;
    int medkit_max_count;
    int medkit_heal_power;
	int zombies_spawn_timer;
	int dragons_spawn_timer;
};
