#include "romania_map.h"
#include "map_tools.h"

struct Map *create_map(int numlocations){
	// Create a map
	struct Map *map = addMap(numlocations);
	// numlocations = 30 for the locations in our Romania input
	// We can adjust this later to fetch data from a file or API
	// e.g CSV, OpenStreet Map, Google Map

	// Add the neighbors for each of the locationlist
	// According to the example Romania map - first 10 only
	addNeighbor(map, 0, 1);

	addNeighbor(map, 1, 2);
	addNeighbor(map, 1, 4);
	addNeighbor(map, 1, 0);

	addNeighbor(map, 2, 1);
	addNeighbor(map, 2, 19);
	addNeighbor(map, 2, 20);

	addNeighbor(map, 3, 26);
	addNeighbor(map, 3, 4);

	addNeighbor(map, 4, 1);
	addNeighbor(map, 4, 3);

	addNeighbor(map, 5, 6);
	addNeighbor(map, 5, 26);

	addNeighbor(map, 6, 5);
	addNeighbor(map, 6, 7);

	addNeighbor(map, 7, 8);
	addNeighbor(map, 7, 6);
	addNeighbor(map, 7, 23);

	addNeighbor(map, 8, 9);

	addNeighbor(map, 9, 8);
	addNeighbor(map, 9, 11);

		return map;
	}
