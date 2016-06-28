#include "config.h"

Config& Config::instance()
{
	static Config config;
	return config;
};

void Config::Parse(char* file_name)
{
	delete importer;
	importer = new Json_importer(file_name);
};

void Config::SetVariables()
{
    ground_symbol = importer->get_char("ground", "symbol");
    wall_symbol = importer->get_char("wall", "symbol");
    knight_hp = importer->get_int("knight", "hp");
    knight_damage = importer->get_int("knight", "damage");
    knight_symbol = importer->get_char("knight", "symbol");
    princess_hp = importer->get_int("princess", "hp");
    princess_symbol = importer->get_char("princess", "symbol");
    zombie_hp = importer->get_int("zombie", "hp");
    zombie_damage = importer->get_int("zombie", "damage");
    zombie_symbol = importer->get_char("zombie", "symbol");
    dragon_hp = importer->get_int("dragon", "hp");
    dragon_damage = importer->get_int("dragon", "damage");
    dragon_symbol = importer->get_char("dragon", "symbol");
    wizard_hp = importer->get_int("wizard", "hp");
    wizard_damage = importer->get_int("wizard", "damage");
    wizard_symbol = importer->get_char("wizard", "symbol");
	medkit_symbol = importer->get_char("medkit", "symbol");
    medkit_timer = importer->get_int("medkit", "timer");
    medkit_max_count = importer->get_int("medkit", "max_count");
    medkit_heal_power = importer->get_int("medkit", "heal_power");
    dragons_spawn_symbol = importer->get_char("dragon_spawn", "symbol");
    dragons_spawn_timer = importer->get_int("dragons_spawn", "timer");
    zombies_spawn_symbol = importer->get_char("zombies_spawn", "symbol");
	zombies_spawn_timer = importer->get_int("zombies_spawn", "timer");
    fireball_damage = importer->get_int("fireball", "damage");
};

Config::~Config()
{
	delete this->importer;
};
