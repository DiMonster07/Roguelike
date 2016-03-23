#include "gamemanager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

const int att_range = 3;

GameManager::GameManager(const char *name_map)
{
	this->map = Map(name_map);
}

void GameManager::refreshInfo()
{
	mvprintw(0, 61, "%s", "INFO");
	mvprintw(1, 61, "%s%d", "Health: " ,this->heroes[0]->hitPoints());
	mvprintw(2, 61, "%s%d", "Damage: " ,this->heroes[0]->damage());
}

void GameManager::refreshGrid()
{
	this->map.printMap();
	this->refreshInfo();
	refresh();
}

void GameManager::generateUnits()
{
	int x = this->heroes[0]->getX();
	int y = this->heroes[0]->getY();
	while (1)
	{
		x = (x > this->map.cols/2 - 1) ? x - this->map.cols/2 + 1 : 
			x + this->map.cols/2 - 1;
		y = (y > this->map.rows/2 - 1) ? y - this->map.rows/2 + 1 : 
			y + this->map.rows/2 - 1;
		if (this->map.map[y][x] == '.') break;
	}
	this->addUnit('P', x, y);
	int i = 0;
	srand(time(0));
	while(i < 30)
	{
		x = rand() % (this->map.cols - 1) + 1;
		y = rand() % (this->map.rows - 1) + 1;
		if (this->map.map[y][x] == '.')
		{
			this->addUnit('Z', x, y);
			i++;
		}
	}
}

void GameManager::selectStartPos(WINDOW *win)
{
	clear();
	this->heroes.push_back(new Knight(30, 3, 1, 1));
	this->refreshGrid();
	while(1)
	{
		int command = getch();
		if (command == ' ') break;
		this->keyCallback(command);
		this->refreshGrid();
	}
	clear();
	refresh();
	mvprintw(0, 0, "%s", "Please press any key. Good luck!");
	getch();
	clear();
}

int GameManager::keyCallback(int key)
{
	switch(key)
	{
		case KEY_UP: this->heroes[0]->move(this->map, 0, -1); break;
		case KEY_DOWN: this->heroes[0]->move(this->map, 0, 1); break;
		case KEY_RIGHT: this->heroes[0]->move(this->map, 1, 0); break;
		case KEY_LEFT: this->heroes[0]->move(this->map, -1, 0); break;
		case 27: return 1;
	}
	return 0;
}

void GameManager::unitsMove()
{
	int x_k = this->heroes[0]->getX();
	int y_k = this->heroes[0]->getY();
	for (int i = 0; i < this->monsters.size(); i++)
	{
		srand(time(0));
		int x_m = this->monsters[i]->getX();
		int y_m = this->monsters[i]->getY();
		if ((x_m + att_range >= x_k) || (x_m - att_range <= x_k) &&
			(y_m + att_range >= y_k) || (y_m - att_range <= y_k))
		{
			x_m = (x_k - x_m) < 0 ? -1 : 1;
			y_m = (y_k - y_m) < 0 ? -1 : 1;
		}
		else
		{
			x_m = rand() % 2 - 1;
			y_m = rand() % 2 - 1;	
		}
		this->monsters[i]->move(this->map, x_m, y_m);
	}
}

void GameManager::addUnit(char c, int x, int y)
{
	 switch(c)
	 {
	 	case 'P': this->heroes.push_back(new Princess(1, 0, x, y)); 
	 	case 'Z': this->monsters.push_back(new Zombie(4, 1, x, y));
	 	case 'D': this->monsters.push_back(new Dragon(70, 25, x, y));
	 }
	 this->map.addCharacter(c, x, y);
}

