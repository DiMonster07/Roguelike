#include "config.h"

Config& Config::instance()
{
	static Config config;
	return config;
};

void Config::parse(char* file_name)
{
	delete importer;
	importer = new Json_importer(file_name);
};

void Config::setVariables()
{
    GROUND_SYMBOL = importer->get_char("ground", "symbol");
    WALL_SYMBOL = importer->get_char("wall", "symbol");
    knight_health = importer->get_int("knight", "hp");
	knight_max_health = importer->get_int("knight", "max_hp");
    knight_damage = importer->get_int("knight", "damage");
    KNIGHT_SYMBOL = importer->get_char("knight", "symbol");
    princess_health = importer->get_int("princess", "hp");
    PRINCESS_SYMBOL = importer->get_char("princess", "symbol");
    zombie_health = importer->get_int("zombie", "hp");
	zombie_max_health = importer->get_int("zombie", "max_hp");
    zombie_damage = importer->get_int("zombie", "damage");
    ZOMBIE_SYMBOL = importer->get_char("zombie", "symbol");
    dragon_health = importer->get_int("dragon", "hp");
	dragon_max_health = importer->get_int("dragon", "max_hp");
    dragon_damage = importer->get_int("dragon", "damage");
    DRAGON_SYMBOL = importer->get_char("dragon", "symbol");
    wizard_health = importer->get_int("wizard", "hp");
	wizard_max_health = importer->get_int("wizard", "max_hp");
    wizard_damage = importer->get_int("wizard", "damage");
    WIZARD_SYMBOL = importer->get_char("wizard", "symbol");
	MEDKIT_SYMBOL = importer->get_char("medkit", "symbol");
    medkit_max_count = importer->get_int("medkit", "max_count");
	medkit_spawn_timer = importer->get_int("medkit", "timer");
    medkit_heal_power = importer->get_int("medkit", "heal_power");
    DRAGONS_SPAWN_SYMBOL = importer->get_char("dragons_spawn", "symbol");
    dragons_spawn_timer = importer->get_int("dragons_spawn", "timer");
    ZOMBIES_SPAWN_SYMBOL = importer->get_char("zombies_spawn", "symbol");
	zombies_spawn_timer = importer->get_int("zombies_spawn", "timer");
    fireball_damage = importer->get_int("fireball", "damage");
};

Config::~Config()
{
	delete this->importer;
};
