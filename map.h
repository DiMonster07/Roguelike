#pragma once
class Map 
{		
public:
	int cols, rows;
	char **map;
	Map() {};
	Map(const char *name_map);
	void addCharacter(char ch, int x, int y);
	void printMap();
};