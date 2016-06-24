#include "meta.h"

class MapConstructor
{
public:
    MapConstructor() { };
	static MapConstructor& instance();
    char* createMap();
    void changeMap(char* nameMap);
};
