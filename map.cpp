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
	this->map = (char**)malloc(this->rows * sizeof(char*));
	for (int i = 0; i < this->rows; i++)
	{
		this->map[i] = (char*)malloc(2 * this->rows * sizeof(char));
		for (int j = 0; j < this->cols; j++)
		{
			input >> c;
			this->map[i][j] = c; 
		}
	}
}

void Map::addCharacter(char ch, int x, int y)
{
	this->map[y][x] = ch;
}

void Map::printMap(WINDOW *win)
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			switch (this->map[i][j])
			{
				case WALL_SYMBOL: wattron(win, COLOR_PAIR(WALL)); mvwprintw(win, i, j, 
					"%c", this->map[i][j]); break;
				case GROUND_SYMBOL: wattron(win, COLOR_PAIR(GROUND)); mvwprintw(win, 
					i, j, "%c", this->map[i][j]); break;
				case KNIGHT_SYMBOL: wattron(win, COLOR_PAIR(KNIGHT)); mvwprintw(win, 
					i, j, "%c", this->map[i][j]); break;
				case PRINCESS_SYMBOL: wattron(win, COLOR_PAIR(PRINCESS)); mvwprintw(win,
					i, j, "%c", this->map[i][j]); break;
				case DRAGON_SYMBOL: wattron(win, COLOR_PAIR(DRAGON)); mvwprintw(win, 
					i, j, "%c", this->map[i][j]); break;
				case ZOMBIE_SYMBOL: wattron(win, COLOR_PAIR(ZOMBIE)); mvwprintw(win, 
					i, j, "%c", this->map[i][j]); break;
			}
		}
	}
	wattron(win, COLOR_PAIR(BASE));
}