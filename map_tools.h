#ifndef MAP_TOOLS_H
#define MAP_TOOLS_H

#include <stdlib.h>
#include "map.h"

/* Prototypes for map helper functions; implementations moved to map_tools.c */
struct Map *addMap(int numlocations);
void addNeighbor(struct Map *map, int sourceloc, int destloc);

#endif  // MAP_TOOLS_H