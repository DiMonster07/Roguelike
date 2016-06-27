#include "mapmanager.h"

using namespace boost::filesystem;

<<<<<<< HEAD
bool my_sort(MapInfo lm, MapInfo rm) { return (lm.name < rm.name); };

void MapManager::mapConstruct()
{
    std::vector<std::vector<char>> map;
    std::string map_name;
    if (this->selectMap(&map, &map_name))
    {
        this->changeMap(&map);
        this->writeMap(&map, map_name);
    }
=======
void MapManager::mapConstruct()
{
<<<<<<< HEAD
    std::vector<std::vector<char>> map;
    std::string map_name;
    if (this->selectMap(&map, &map_name)) this->changeMap(&map);
    this->writeMap(&map, map_name);
=======
    std::string name_map = this->selectMap();
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
};

int MapManager::selectMap(std::vector<std::vector<char>> *map, std::string *map_name)
{
	std::vector<MapInfo>maps_list = getMapsList(DEFAULT_DIR, MAP_EXTENSION);
	std::sort(maps_list.begin(), maps_list.end(), my_sort);
	int cursor = 0;
	bool thp = true;
	while(thp)
	{
		this->printMenuMap(maps_list, cursor);
		int command = wgetch(this->main_win);
		switch (command)
		{
			case KEY_UP: cursor =   (--cursor == -1 ?
									   cursor = maps_list.size() - 1 : cursor);
									   break;
			case KEY_DOWN: cursor = (++cursor == maps_list.size() ?
									   cursor = 0 : cursor);
									   break;
			case KEY_ENTER1: thp = false; break;
			case KEY_N: thp = false;
                        *map_name = this->selectNameMap(maps_list.size());
        		 		maps_list.push_back(MapInfo(*map_name, 0, 0));
        				cursor = maps_list.size() - 1;
        				*map = this->createMap(maps_list[cursor].name);
                        maps_list.back().sx = this->sizeX;
                        maps_list.back().sy = this->sizeY;
                        return 1;
        				break;
            case 27: return 0;
		}
	}
    if (!this->readMap(maps_list[cursor].name, map)) return 0;
    *map_name = maps_list[cursor].name;
    return 1;
};

int MapManager::selectMap(std::string *map_name)
{
<<<<<<< HEAD
    std::vector<MapInfo>maps_list = getMapsList(DEFAULT_DIR, MAP_EXTENSION);
	std::sort(maps_list.begin(), maps_list.end(), my_sort);
=======
    mvwprintw(this->main_win, size_list + 5, 2, "%s %s", "Input map name and",
	                                                     "press enter: ");
	curs_set(TRUE);
	nocbreak();
	echo();
	char str[30];
	wgetstr(this->main_win, str);
	noecho();
	cbreak();
	curs_set(FALSE);
	return std::string(str);
>>>>>>> d40d1754a218ccb451970f1c07c4610067623d2f
};

int MapManager::selectMap(std::vector<std::vector<char>> *map, std::string *map_name)
{
	std::vector<std::string>maps_list = getFilesList(DEFAULT_DIR, MAP_EXTENSION);
	std::sort(maps_list.begin(), maps_list.end());
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
	int cursor = 0;
	bool thp = true;
	while(thp)
	{
		this->printMenuMap(maps_list, cursor);
		int command = wgetch(this->main_win);
		switch (command)
		{
			case KEY_UP: cursor =   (--cursor == -1 ?
									   cursor = maps_list.size() - 1 : cursor);
									   break;
			case KEY_DOWN: cursor = (++cursor == maps_list.size() ?
									   cursor = 0 : cursor);
									   break;
			case KEY_ENTER1: thp = false; break;
<<<<<<< HEAD
            case 27: return 0;
		}
	}
    *map_name = maps_list[cursor].name;
    return 1;
=======
			case KEY_N: thp = false;
				 		maps_list.push_back(
							this->selectNameMap(maps_list.size()) + MAP_EXTENSION);
						cursor = maps_list.size() - 1;
						*map = this->createMap(maps_list[cursor]);
                        *map_name = maps_list[cursor];
                        return 1;
						break;
            case 27: return 0;
		}
	}
<<<<<<< HEAD
    if (!this->readMap(maps_list[cursor], map)) return 0;
    *map_name = maps_list[cursor];
    return 1;
=======
    return maps_list[cursor];
>>>>>>> d40d1754a218ccb451970f1c07c4610067623d2f
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
};

std::vector<std::vector<char>> MapManager::createMap(std::string name_map)
{
    this->selectSizeMap();
    std::vector<std::vector<char>> map;
    this->fillMap(&map);
    return map;
<<<<<<< HEAD
};

void MapManager::changeMap(std::vector<std::vector<char>> *map)
{
=======
};

void MapManager::changeMap(std::vector<std::vector<char>> *map)
{
    int command;
    Cursor cursor(0, Point(1, 1));
    this->printMap(map, &cursor);
    this->printUnitsPanel(&cursor);
    while(this->callbackCreator(command = wgetch(this->main_win), &cursor, map))
    {
        this->printMap(map, &cursor);
        this->printUnitsPanel(&cursor);
    }
};

void MapManager::printMap(std::vector<std::vector<char>> *map, Cursor *csr)
{
    wclear(this->main_win);
    for (int i = 0; i < this->sizeY; i++)
		for (int j = 0; j < this->sizeX; j++)
            mvwprintw(this->main_win, i, j, "%c", (*map)[i][j]);
    mvwprintw(this->main_win, csr->xy.y, csr->xy.x, "%c", units_symbols[csr->pos]);
    wrefresh(this->main_win);
};

void MapManager::selectSizeMap()
{
    int command;
    do
    {
        getmaxyx(stdscr, this->sizeY, this->sizeX);
        this->sizeX = this->sizeX - INFO_WIN_WIDTH;
        wclear(this->main_win);
        mvwprintw(this->main_win, 0, 1, "%s %s %s %s. Current size: x:%d, y:%d",
                                                     "Change size of the",
                                                     "terminal to select",
                                                     "size of the map.",
                                                     "After press ENTER",
                                                     this->sizeX, this->sizeY);
        wrefresh(this->main_win);
    }
    while(command = wgetch(this->info_win) != KEY_ENTER1);
};

void MapManager::moveUnit(Cursor *csr, Point dir)
{
    Point tp = csr->xy + dir;
    if (tp.x != 0 && tp.x != this->sizeX - 1 &&
        tp.y != 0 && tp.y != this->sizeY - 1)
        csr->xy = tp;
};

void MapManager::setUnitInPlace(std::vector<std::vector<char>> *map,
                                                     Cursor *csr)
{
    char symb = units_symbols[csr->pos];
    if (symb == KNIGHT_SYMBOL || symb == PRINCESS_SYMBOL)
    {
        (*map)[csr->xy.y][csr->xy.x] =
            this->findUnit(map, symb) ? (*map)[csr->xy.y][csr->xy.x] : symb;
    } else (*map)[csr->xy.y][csr->xy.x] = symb;
};

int MapManager::findUnit(std::vector<std::vector<char>> *map, char unit_symbol)
{
    int is = 0;
    for (int i = 0; i < this->sizeY; i++)
		for (int j = 0; j < this->sizeX; j++)
            if ((*map)[i][j] == unit_symbol) return 1;
    return 0;
};

int MapManager::readMap(std::string name_map, std::vector<std::vector<char>> *map)
{
    std::ifstream input(DEFAULT_DIR + name_map);
	input >> this->sizeY >> this->sizeX;
    char c;
	for (int i = 0; i < this->sizeY; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < this->sizeX; j++)
        {
            input >> c;
            row.push_back(c);
        }
		(*map).push_back(row);
	}
    return 1;
};

void MapManager::writeMap(std::vector<std::vector<char>> *map,
                              std::string name_map)
{
    std::ofstream output(DEFAULT_DIR + name_map);
    output << this->sizeY << " " << this->sizeX << std::endl;
    for (int i = 0; i < this->sizeY; i++)
    {
		for (int j = 0; j < this->sizeX; j++)
            output << (*map)[i][j];
        output << std::endl;
    }
    output.close();
};

void MapManager::writeMap(std::string name_map)
{
<<<<<<< HEAD
    std::ofstream output(DEFAULT_DIR + name_map);
    output << this->sizeY << " " << this->sizeX << std::endl;
	for (int i = 0; i < this->sizeY; i++)
    {
		for (int j = 0; j < this->sizeX; j++)
        {
            char out = ((i == 0 || i == this->sizeY - 1) ||
                        (j == 0 || j == this->sizeX - 1) ?
                        WALL_SYMBOL : GROUND_SYMBOL);
            output << out;
        }
        output << std::endl;
=======
    int sizeX, sizeY;
    this->selectSizeMap(&sizeX, &sizeY);
    std::vector<std::vector<char>> map;
    this->fillMap(&map, sizeX, sizeY);
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
    int command;
    Cursor cursor(0, Point(1, 1));
    this->printMap(map, &cursor);
    this->printUnitsPanel(&cursor);
    while(this->callbackCreator(command = wgetch(this->main_win), &cursor, map))
    {
<<<<<<< HEAD
        this->printMap(map, &cursor);
        this->printUnitsPanel(&cursor);
=======
        this->printMap(&map, sizeX, sizeY);
>>>>>>> d40d1754a218ccb451970f1c07c4610067623d2f
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
    }
};

void MapManager::printMap(std::vector<std::vector<char>> *map, Cursor *csr)
{
    wclear(this->main_win);
    for (int i = 0; i < this->sizeY; i++)
		for (int j = 0; j < this->sizeX; j++)
        {
            wattron(this->main_win, COLOR_PAIR(units_color[(*map)[i][j]]));
            mvwprintw(this->main_win, i, j, "%c", (*map)[i][j]);
        }
    wattron(this->main_win, COLOR_PAIR(units_color[units_symbols[csr->pos]]));
    mvwprintw(this->main_win, csr->xy.y, csr->xy.x, "%c", units_symbols[csr->pos]);
    wrefresh(this->main_win);
    wattron(this->main_win, COLOR_PAIR(BASE_COLOR));
};

void MapManager::selectSizeMap()
{
    int command;
    do
    {
        getmaxyx(stdscr, this->sizeY, this->sizeX);
        this->sizeX = this->sizeX - INFO_WIN_WIDTH;
        wclear(this->main_win);
        mvwprintw(this->main_win, 0, 1, "%s %s %s %s. Current size: x:%d, y:%d",
                                                     "Change size of the",
                                                     "terminal to select",
                                                     "size of the map.",
                                                     "After press ENTER",
                                                     this->sizeX, this->sizeY);
        wrefresh(this->main_win);
    }
    while(command = wgetch(this->info_win) != KEY_ENTER1);
};

<<<<<<< HEAD
void MapManager::moveUnit(Cursor *csr, Point dir)
{
    Point tp = csr->xy + dir;
    if (tp.x != 0 && tp.x != this->sizeX - 1 &&
        tp.y != 0 && tp.y != this->sizeY - 1)
        csr->xy = tp;
};

void MapManager::setUnitInPlace(std::vector<std::vector<char>> *map,
                                                     Cursor *csr)
{
    char symb = units_symbols[csr->pos];
    if (symb == KNIGHT_SYMBOL || symb == PRINCESS_SYMBOL)
    {
        (*map)[csr->xy.y][csr->xy.x] =
            this->findUnit(map, symb) ? (*map)[csr->xy.y][csr->xy.x] : symb;
    } else (*map)[csr->xy.y][csr->xy.x] = symb;
};

int MapManager::findUnit(std::vector<std::vector<char>> *map, char unit_symbol)
{
    int is = 0;
    for (int i = 0; i < this->sizeY; i++)
		for (int j = 0; j < this->sizeX; j++)
            if ((*map)[i][j] == unit_symbol) return 1;
    return 0;
};

int MapManager::readMap(std::string name_map, std::vector<std::vector<char>> *map)
{
    std::ifstream input(DEFAULT_DIR + name_map);
	input >> this->sizeY >> this->sizeX;
    char c;
	for (int i = 0; i < this->sizeY; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < this->sizeX; j++)
        {
            input >> c;
            row.push_back(c);
        }
		(*map).push_back(row);
	}
    return 1;
=======
void MapManager::fillMap(std::vector<std::vector<char>> *map)
{
    for (int i = 0; i < this->sizeY; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < this->sizeX; j++)
            row.push_back(((i == 0 || i == this->sizeY - 1) ||
                           (j == 0 || j == this->sizeX - 1) ?
                           WALL_SYMBOL : GROUND_SYMBOL));
		map->push_back(row);
	}
};

std::vector<std::string> MapManager::getFilesList(std::string directory,
												  std::string file_extension)
{
	std::vector<std::string>files_list;
	path p(directory);
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
        if (!is_directory(i->path()) && i->path().extension() == file_extension)
			files_list.push_back(i->path().filename().c_str());
	return files_list;
};

std::string MapManager::selectNameMap(int size_list)
{
    mvwprintw(this->main_win, size_list + 5, 2, "%s %s", "Input map name and",
	                                                     "press enter: ");
	curs_set(TRUE);
	nocbreak();
	echo();
	char str[30];
	wgetstr(this->main_win, str);
	noecho();
	cbreak();
	curs_set(FALSE);
	return std::string(str);
};

void MapManager::printMenuMap(std::vector<std::string>maps_list, int csr)
{
	wclear(this->main_win);
	mvwprintw(this->main_win, 1, 2, "%s %s", "Select map for editing or press n",
											 "for create new map:");
	for (int i = 0; i < maps_list.size(); i++)
	{
		std::string str = (i == csr ? maps_list[i] + CURSOR : maps_list[i]);
		mvwprintw(this->main_win, i + 3, 5, "%s", str.c_str());
	}
	wrefresh(this->main_win);
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
};

<<<<<<< HEAD
void MapManager::printUnitsPanel(Cursor *csr)
=======
void MapManager::writeMap(std::vector<std::vector<char>> *map,
                              std::string name_map)
>>>>>>> d40d1754a218ccb451970f1c07c4610067623d2f
{
<<<<<<< HEAD
    std::ofstream output(DEFAULT_DIR + name_map);
    output << this->sizeY << " " << this->sizeX << std::endl;
    for (int i = 0; i < this->sizeY; i++)
    {
		for (int j = 0; j < this->sizeX; j++)
            output << (*map)[i][j];
        output << std::endl;
    }
    output.close();
=======
    wclear(this->info_win);
    for (int i = 0; i < UNITS_COUNT; i++)
    {
        std::string str = (i == csr->pos ? units_name[units_symbols[i]] + CURSOR :
                                           units_name[units_symbols[i]]);
        mvwprintw(this->info_win, i + 1, 1, "%c %s",
                  units_symbols[i], str.c_str());
    }
    wrefresh(this->info_win);
};

int MapManager::callbackCreator(int command, Cursor *csr,
                                std::vector<std::vector<char>> *map)
{
    switch(command)
    {
        case KEY_UP: this->moveUnit(csr, LEFT_DIRECTION); break;
        case KEY_DOWN: this->moveUnit(csr, RIGHT_DIRECTION); break;
        case KEY_LEFT: this->moveUnit(csr, UP_DIRECTION); break;
        case KEY_RIGHT: this->moveUnit(csr, DOWN_DIRECTION); break;
        case KEY_W: (--csr->pos == -1 ? csr->pos = UNITS_COUNT - 1 : csr->pos);
                                                    break;
        case KEY_S: (++csr->pos == UNITS_COUNT ? csr->pos = 0 : csr->pos);
                                                    break;
        case KEY_SPACE: this->setUnitInPlace(map, csr); break;
        case KEY_ENTER1: return 0; break;
    }
    return 1;
};

MapManager& MapManager::instance()
{
    static MapManager manager;
	return manager;
};

void MapManager::initialize(WINDOW* win1, WINDOW* win2)
{
    this->main_win = win1;
    this->info_win = win2;
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
};

void MapManager::writeMap(std::string name_map)
{
    std::ofstream output(DEFAULT_DIR + name_map);
    output << this->sizeY << " " << this->sizeX << std::endl;
	for (int i = 0; i < this->sizeY; i++)
    {
		for (int j = 0; j < this->sizeX; j++)
        {
            char out = ((i == 0 || i == this->sizeY - 1) ||
                        (j == 0 || j == this->sizeX - 1) ?
                        WALL_SYMBOL : GROUND_SYMBOL);
            output << out;
        }
        output << std::endl;
    }
    output.close();
};

void MapManager::fillMap(std::vector<std::vector<char>> *map)
{
    for (int i = 0; i < this->sizeY; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < this->sizeX; j++)
            row.push_back(((i == 0 || i == this->sizeY - 1) ||
                           (j == 0 || j == this->sizeX - 1) ?
                           WALL_SYMBOL : GROUND_SYMBOL));
		map->push_back(row);
	}
};

std::vector<MapInfo> MapManager::getMapsList(std::string directory,
										     std::string file_extension)
{
	std::vector<MapInfo>files_list;
	path p(directory);
    for (auto i = directory_iterator(p); i != directory_iterator(); i++)
        if (!is_directory(i->path()) && i->path().extension() == file_extension)
			files_list.push_back(MapInfo(i->path().filename().c_str(), 0, 0));
    for (int i = 0; i < files_list.size(); i++)
    {
        std::ifstream input(files_list[i].name);
        input >> files_list[i].sy >> files_list[i].sx;
        input.close();
    }
	return files_list;
};

std::string MapManager::selectNameMap(int size_list)
{
    mvwprintw(this->main_win, size_list + 5, 2, "%s %s", "Input map name and",
	                                                     "press enter: ");
	curs_set(TRUE);
	nocbreak();
	echo();
	char str[30];
	wgetstr(this->main_win, str);
	noecho();
	cbreak();
	curs_set(FALSE);
	return std::string(str) + MAP_EXTENSION;
};

void MapManager::printMenuMap(std::vector<MapInfo>maps_list, int csr)
{
	wclear(this->main_win);
	mvwprintw(this->main_win, 1, 2, "%s %s", "Select map for editing or press n",
											 "for create new map:");
    int sx, sy;
    getmaxyx(stdscr, sy, sx);
    sx = sx - INFO_WIN_WIDTH;
    int c = 0;
	for (int i = 0; i < maps_list.size(); i++)
	{
        if (sx >= maps_list[i].sx && sy >= maps_list[i].sy)
        {
    		std::string str = (i == csr ? maps_list[i].name + CURSOR : maps_list[i].name);
    		mvwprintw(this->main_win, c + 3, 5, "%s", str.c_str());
            c++;
        }
	}
    if (c == 0)
    {
        wclear(this->main_win);
    	mvwprintw(this->main_win, 1, 2, "%s %s", "Please, for select maps",
                                                 "changes size terminal");
    }
	wrefresh(this->main_win);
};

void MapManager::printUnitsPanel(Cursor *csr)
{
    wclear(this->info_win);
    for (int i = 0; i < UNITS_COUNT; i++)
    {
        std::string str = (i == csr->pos ? units_name[units_symbols[i]] + CURSOR :
                                           units_name[units_symbols[i]]);
        wattron(this->info_win, COLOR_PAIR(units_color[units_symbols[i]]));
        mvwprintw(this->info_win, i + 1, 1, "%c", units_symbols[i]);
        wattron(this->info_win, COLOR_PAIR(BASE_COLOR));
        mvwprintw(this->info_win, i + 1, 3, "%s", str.c_str());
    }
    wrefresh(this->info_win);
};

int MapManager::callbackCreator(int command, Cursor *csr,
                                std::vector<std::vector<char>> *map)
{
    switch(command)
    {
        case KEY_W: --csr->pos == -1 ? csr->pos = UNITS_COUNT - 1 : csr->pos;
                    break;
        case KEY_S: ++csr->pos == UNITS_COUNT ? csr->pos = 0 : csr->pos;
                    break;
        case KEY_UP: this->moveUnit(csr, LEFT_DIRECTION); break;
        case KEY_DOWN: this->moveUnit(csr, RIGHT_DIRECTION); break;
        case KEY_LEFT: this->moveUnit(csr, UP_DIRECTION); break;
        case KEY_RIGHT: this->moveUnit(csr, DOWN_DIRECTION); break;
        case KEY_SPACE: this->setUnitInPlace(map, csr); break;
        case KEY_ENTER1: return 0; break;
    }
    return 1;
};

MapManager& MapManager::instance()
{
    static MapManager manager;
	return manager;
};

void MapManager::initialize(WINDOW* win1, WINDOW* win2)
{
    this->main_win = win1;
    this->info_win = win2;
};
