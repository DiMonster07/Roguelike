#include "mapconstructor.h"

static MapConstructor& instance()
{
    static MapConstructor constructor();
	return MapConstructor;
};
