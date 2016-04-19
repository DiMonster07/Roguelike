#include "map.h"
#include "gamemanager.h"
#include "units.h"
#include <malloc.h>
#include <fstream>
#include <iostream>

Map::Map(const char* name_map)
{
	std::ifstream input(name_map);
	char c;
	input >> this->rows;
	input >> this->cols;
	for (int i = 0; i < this->rows; i++)
	{
		std::vector<Actor*> row;
		for (int j = 0; j < this->cols; j++)
		{
			input >> c;
			switch(c)
			{
				case WALL_SYMBOL: row.push_back(new Wall(3, i, j)); break;
				case GROUND_SYMBOL: row.push_back(new Ground(1, i, j)); break;
			}
		}
		map.push_back(row);
	}
}

void Map::addCharacter(char ch, int x, int y)
{
	//this->map[y][x] = ch;
}

void Map::printMap(WINDOW *win)
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			wattron(win, COLOR_PAIR(this->map[i][j]->get_color()));
			mvwprintw(win, i, j, "%c", this->map[i][j]->get_symbol());
		}
	}
	wattron(win, COLOR_PAIR(BASE_COLOR));
}
