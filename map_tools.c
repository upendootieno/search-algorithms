#include <stdlib.h>
#include "map_tools.h"

/* Implementation of helper functions for Map operations. These were moved
   out of headers to avoid multiple-definition linker errors and to fix
   allocation issues. */

struct LocationNode *addLocation(int locationid){
    struct LocationNode *location = malloc(sizeof(struct LocationNode));
    if (!location) return NULL;
    location->locationid = locationid;
    location->neighbor = NULL;
    return location;
}

struct Map *addMap(int numlocations){
    struct Map *map = malloc(sizeof(struct Map));
    if (!map) return NULL;
    map->numlocations = numlocations;

    /* Initialize the fixed-size locationlist in the Map struct. The original
       code attempted to malloc a separate locationlist while Map already
       contains a fixed array. We simply populate the existing array up to
       numlocations (caller must ensure numlocations <= capacity). */
    for (int u = 0; u < map->numlocations && u < 30; u++){
        struct LocationNode *location = addLocation(u);
        map->locationlist[u] = location;
    }
    return map;
}

void addNeighbor(struct Map *map, int sourceloc, int destloc){
    struct LocationNode *newlocation = addLocation(destloc);
    if (!newlocation) return;
    newlocation->neighbor = map->locationlist[sourceloc];
    map->locationlist[sourceloc] = newlocation;
}
