#include "gamemanager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

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
		case KEY_UP: this->heroes[0]->move(this->map, NONEX, UP); break;
		case KEY_DOWN: this->heroes[0]->move(this->map, NONEX, DOWN); break;
		case KEY_RIGHT: this->heroes[0]->move(this->map, RIGHT, NONEY); break;
		case KEY_LEFT: this->heroes[0]->move(this->map, LEFT, NONEY); break;
		case 27: return 1;
	}
	return 0;
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

