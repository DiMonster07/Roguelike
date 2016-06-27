#include "mapmanager.h"

using namespace boost::filesystem;

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

void MapManager::mapConstruct()
{
    std::string name_map = this->selectMap();
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

std::string MapManager::selectMap()
{
	std::vector<std::string>maps_list = getFilesList(DEFAULT_DIR, MAP_EXTENSION);
	std::sort(maps_list.begin(), maps_list.end());
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
				 		maps_list.push_back(
							this->selectNameMap(maps_list.size()) + MAP_EXTENSION);
						cursor = maps_list.size() - 1;
						this->createMap(maps_list[cursor]);
						break;
            case 27: return 0;
		}
	}
    return maps_list[cursor];
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

void MapManager::createMap(std::string name_map)
{
    this->selectSizeMap();
    std::vector<std::vector<char>> map;
    this->fillMap(&map);
    int command;
    Cursor cursor(0, Point(1, 1));
    this->printMap(&map, &cursor);
    this->printUnitsPanel(&cursor);
    while(this->callbackCreator(command = wgetch(this->main_win), &cursor, &map))
    {
        this->printMap(&map, &cursor);
        this->printUnitsPanel(&cursor);
    }
    this->writeMap(&map, name_map);
};

void MapManager::calcUnitsCount(std::vector<std::vector<char>> *map)
{

};

void MapManager::printUnitsPanel(Cursor *csr)
{
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

void MapManager::changeMap(std::string name_map)
{
    std::vector<std::vector<char>> map = this->readMap(name_map);
};

std::vector<std::vector<char>> MapManager::readMap(std::string name_map)
{
    std::ifstream input(name_map);
    int rows, cols;
	char c;
	input >> rows;
	input >> cols;
    std::vector<std::vector<char>> map;
	for (int i = 0; i < rows; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < cols; j++)
            row.push_back(input.get());
		map.push_back(row);
	}
    return map;
};

void MapManager::writeMap(std::vector<std::vector<char>> *map,
                              std::string name_map)
{
    std::ofstream output(DEFAULT_DIR + name_map);
    output << this->sizeX << " " << this->sizeY << std::endl;
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
