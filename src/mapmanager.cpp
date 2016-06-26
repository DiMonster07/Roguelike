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

void MapManager::printMenuMap(std::vector<std::string>maps_list, int cursor)
{
	wclear(this->main_win);
	mvwprintw(this->main_win, 1, 2, "%s %s", "Select map for editing or press n",
											 "for create new map:");
	for (int i = 0; i < maps_list.size(); i++)
	{
		std::string str = (i == cursor ? maps_list[i] + CURSOR : maps_list[i]);
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
			case KEY_SPACE: thp = false; break;
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
    int sizeX, sizeY;
    this->selectSizeMap(&sizeX, &sizeY);
    std::vector<std::vector<char>> map;
    this->fillMap(&map, sizeX, sizeY);
    int command;
    do
    {
        this->printMap(&map, sizeX, sizeY);
    }
    while(command = wgetch(this->main_win) != KEY_SPACE);
    this->writeMap(&map, name_map);
};

void MapManager::fillMap(std::vector<std::vector<char>> *map, int sizeX, int sizeY)
{
    for (int i = 0; i < sizeY; i++)
	{
		std::vector<char> row;
		for (int j = 0; j < sizeX; j++)
            row.push_back(((i == 0 || i == sizeY - 1) ||
                           (j == 0 || j == sizeX - 1) ?
                           WALL_SYMBOL : GROUND_SYMBOL));
		map->push_back(row);
	}
};

void MapManager::printMap(std::vector<std::vector<char>> *map, int sizeX, int sizeY)
{
    wclear(this->main_win);
    for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
            mvwprintw(this->main_win, i, j, "%c", (*map)[i][j]);
    wrefresh(this->main_win);
};

void MapManager::selectSizeMap(int *sizeX, int *sizeY)
{
    int command;
    do
    {
        getmaxyx(stdscr, *sizeY, *sizeX);
        *sizeX = *sizeX - INFO_WIN_WIDTH;
        wclear(this->main_win);
        mvwprintw(this->main_win, 0, 1, "%s %s %s %s. Current size: x:%d, y:%d",
                                                     "Change size of the",
                                                     "terminal to select",
                                                     "size of the map.",
                                                     "After press SPACE",
                                                     *sizeX, *sizeY);
        wrefresh(this->main_win);
    }
    while(command = wgetch(this->info_win) != KEY_SPACE);
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

};

void MapManager::writeMap(std::string name_map, int sizeX, int sizeY)
{
    std::ofstream output(DEFAULT_DIR + name_map);
    output << sizeY << " " << sizeX << std::endl;
	for (int i = 0; i < sizeY; i++)
    {
		for (int j = 0; j < sizeX; j++)
        {
            char out = ((i == 0 || i == sizeY - 1) ||
                        (j == 0 || j == sizeX - 1) ?
                        WALL_SYMBOL : GROUND_SYMBOL);
            output << out;
        }
        output << std::endl;
    }
    output.close();
};
