#include "map.h"
#include "gamemanager.h"
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

void Map::printMap()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			switch (this->map[i][j])
			{
				case '#': attron(COLOR_PAIR(WALL)); mvprintw(i, j, "%c", this->map[i][j]); break;
				case '.': attron(COLOR_PAIR(LEA)); mvprintw(i, j, "%c", this->map[i][j]); break;
				case 'K': attron(COLOR_PAIR(KNIGHT)); mvprintw(i, j, "%c", this->map[i][j]); break;
				case 'P': attron(COLOR_PAIR(PRINCESS)); mvprintw(i, j, "%c", this->map[i][j]); break;
				case 'D': attron(COLOR_PAIR(DRAGON)); mvprintw(i, j, "%c", this->map[i][j]); break;
				case 'Z': attron(COLOR_PAIR(ZOMBIE)); mvprintw(i, j, "%c", this->map[i][j]); break;
			}
		}
		printw("\n");
	}
	attron(COLOR_PAIR(BASE));
}