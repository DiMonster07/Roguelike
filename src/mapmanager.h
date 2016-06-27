#pragma once
#include "meta.h"
#include "units.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

typedef struct _cursor
{
    int pos;
    Point xy;
    _cursor (int p, Point coord)
    {
<<<<<<< HEAD
        this->pos = p;
        this->xy = coord;
    }
} Cursor;

typedef struct _file
{
    std::string name;
    int sx, sy;
    _file (std::string file_name, int sx, int sy)
    {
        this->name = file_name;
        this->sx = sx;
        this->sy = sy;
    }
} MapInfo;

=======
        pos = p;
        xy = coord;
    }
} Cursor;

>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7

class MapManager
{
private:
    WINDOW *main_win, *info_win;
    int sizeX, sizeY;
public:
    MapManager() { };
	static MapManager& instance();
    void initialize(WINDOW* win1, WINDOW* win2);
    void mapConstruct();
<<<<<<< HEAD
    void printMenuMap(std::vector<MapInfo>maps_list, int csr);
    std::string selectNameMap(int size_list);
    int selectMap(std::vector<std::vector<char>> *map, std::string *map_name);
    int selectMap(std::string *map_name);
    std::vector<MapInfo> getMapsList(std::string directory,
    						         std::string file_extension);
    std::vector<std::vector<char>> createMap(std::string name_map);
=======
    void printMenuMap(std::vector<std::string>maps_list, int csr);
    std::string selectNameMap(int size_list);
    int selectMap(std::vector<std::vector<char>> *map, std::string *map_name);
    std::vector<std::string> getFilesList(std::string directory,
    									  std::string file_extension);
<<<<<<< HEAD
    std::vector<std::vector<char>> createMap(std::string name_map);
    void createMap(std::string name_map, int x, int y);
    void changeMap(std::vector<std::vector<char>> *map);
    int readMap(std::string name_map, std::vector<std::vector<char>> *map);
    void selectSizeMap();
    int callbackCreator(int command, Cursor *csr,
                        std::vector<std::vector<char>> *map);
    void printMap(std::vector<std::vector<char>> *map, Cursor *csr);
    void moveUnit(Cursor *csr, Point dir);
    void setUnitInPlace(std::vector<std::vector<char>> *map, Cursor *csr);
    int findUnit(std::vector<std::vector<char>> *map, char unit_symbol);
    void printUnitsPanel(Cursor *csr);
    void fillMap(std::vector<std::vector<char>> *map);
    void writeMap(std::vector<std::vector<char>> *map, std::string name_map);
    void writeMap(std::string name_map);
=======
    void createMap(std::string name_map);
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
    void createMap(std::string name_map, int x, int y);
    void changeMap(std::vector<std::vector<char>> *map);
    int readMap(std::string name_map, std::vector<std::vector<char>> *map);
    void selectSizeMap();
    int callbackCreator(int command, Cursor *csr,
                        std::vector<std::vector<char>> *map);
    void printMap(std::vector<std::vector<char>> *map, Cursor *csr);
    void moveUnit(Cursor *csr, Point dir);
    void setUnitInPlace(std::vector<std::vector<char>> *map, Cursor *csr);
    int findUnit(std::vector<std::vector<char>> *map, char unit_symbol);
    void printUnitsPanel(Cursor *csr);
    void fillMap(std::vector<std::vector<char>> *map);
    void writeMap(std::vector<std::vector<char>> *map, std::string name_map);
<<<<<<< HEAD
    void writeMap(std::string name_map);
=======
    void writeMap(std::string name_map, int sizeX, int sizeY);
    void printMap(std::vector<std::vector<char>> *map, int sizeX, int sizeY);
>>>>>>> d40d1754a218ccb451970f1c07c4610067623d2f
>>>>>>> 6d54c21a10ac0b6a9a25390aa74bc29c7fad71b7
};
