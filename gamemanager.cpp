#include "gamemanager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>

const int att_range = 2;
long long seed;
bool flag = false;

void collide(Actor* left, Actor* right)
{
	left->collide(right);
}

void GameManager::createWins()
{
	this->game_win = newwin(30, 60, 0, 0);
	this->info_win = newwin(30, 20, 0, 61);
}

GameManager::GameManager(const char *name_map)
{
	this->map = Map(name_map);
}

void GameManager::refreshInfo()
{
	wclear(this->info_win);
	mvwprintw(this->info_win, 0, 0, "%s", "INFO");
	mvwprintw(this->info_win, 1, 0, "Health: %d", this->knight->hitPoints());
	mvwprintw(this->info_win, 2, 0, "Damage: %d", this->knight->get_damage());
	mvwprintw(this->info_win, 3, 0, "Сoordinate: %d %d", this->knight->getX(), 
		this->knight->getY());
	if (flag) mvwprintw(this->info_win, 4, 0, "%s", "Collide");
	wrefresh(this->info_win);
}

void GameManager::refreshGrid()
{
	this->map.printMap(this->game_win);
	this->refreshInfo();
}

void GameManager::generateUnits()
{
	seed = time(0);
	srand(seed++);
	int x = this->knight->getX();
	int y = this->knight->getY();
	while (1)
	{
		int xn = rand() % (this->map.cols - 2) + 1;
		int yn = rand() % (this->map.rows - 2) + 1;
		if ((abs(x - xn) >= this->map.cols / 2 - 1) && (abs(y - yn) >= this->map.rows / 2 - 1) &&
			(this->map.map[yn][xn] == '.')) 
		{
			x = xn;
			y = yn;
			break;
		}
	}
	this->addUnit('P', x, y);
	int i = 0;
	srand(seed++);
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

void GameManager::selectStartPos()
{
	srand(time(0));
	this->knight = new Knight(30, 3, 1, 1);
	this->refreshGrid();
	while(1)
	{
		int command = wgetch(this->game_win);
		if (command == ' ') break;
		this->keyCallback(command);
		this->refreshGrid();
	}
	wrefresh(this->game_win);
	mvwprintw(this->game_win, 0, 0, "%s", "Please press any key. Good luck!");
	wgetch(this->game_win);
	clear();
}

int GameManager::keyCallback(int key)
{
	switch(key)
	{
		case KEY_UP: this->knight->move(this->map, 0, -1); break;
		case KEY_DOWN: this->knight->move(this->map, 0, 1); break;
		case KEY_RIGHT: this->knight->move(this->map, 1, 0); break;
		case KEY_LEFT: this->knight->move(this->map, -1, 0); break;
		case 27: return 1;
	}
	return 0;
}

void GameManager::unitsMove()
{
	srand(seed++);
	int x_k = this->knight->getX();
	int y_k = this->knight->getY();
	for (int i = 0; i < this->actors.size(); i++)
	{
		int x_m = this->actors[i]->getX();
		int y_m = this->actors[i]->getY();
		if ((abs(x_m - x_k) <= att_range) && (abs(y_m - y_k) <= att_range))
		{
			x_m = (x_k - x_m) < 0 ? -1 : 1;
			y_m = (y_k - y_m) < 0 ? -1 : 1;
		}
		else
		{
			x_m = rand() % 3 - 1;
			y_m = rand() % 3 - 1;	
		}
		this->actors[i]->move(this->map, x_m, y_m);
		x_m = this->actors[i]->getX();
		y_m = this->actors[i]->getY();	
		if (abs(x_m - x_k) == 1 && abs(y_m - y_k) == 1)
		{
			collide(this->knight, this->actors[i]);
		}
	}
}

void GameManager::addUnit(char c, int x, int y)
{
	 switch(c)
	 {
	 	case 'P': this->princess = new Princess(1, 0, x, y); break; 
	 	case 'Z': this->actors.push_back(new Zombie(4, 1, x, y)); break;
	 	case 'D': this->actors.push_back(new Dragon(70, 25, x, y)); break;
	 }
	 this->map.addCharacter(c, x, y);
}

