#pragma once
#include "meta.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

class MapManager
{
private:
    WINDOW *main_win, *info_win;
public:
    MapManager() { };
	static MapManager& instance();
    void initialize(WINDOW* win1, WINDOW* win2);
    void mapConstruct();
    void printMenuMap(std::vector<std::string>maps_list, int cursor);
    std::string selectNameMap(int size_list);
    std::string selectMap();
    std::vector<std::string> getFilesList(std::string directory,
    									  std::string file_extension);
    void createMap(std::string name_map);
    void changeMap(std::string name_map);
    std::vector<std::vector<char>> readMap(std::string name_map);
    void selectSizeMap(int *sizeX, int *sizeY);
    void writeMap(std::vector<std::vector<char>> map, std::string name_map);
};
