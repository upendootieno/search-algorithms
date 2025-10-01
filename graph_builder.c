#include <stdio.h>
#include <stdlib.h>

// Linked List to represent locations and neighbors
typedef struct LocationNode{
	int locationid; // location id - integer value representing labeled location
	struct LocationNode* neighbor; // pointer to the neighbor node / location
};

// Function for adding new locations
struct LocationNode *addLocation(int locationid){
	struct LocationNode *location = malloc(sizeof(struct LocationNode));
	location -> locationid = locationid;
	location -> neighbor = NULL;
	return location;
};

// Graph structure to represent the entire map
typedef struct Map{
	int numlocations; // Specify number of locations in the map
	// Array of location nodes
	struct LocationNode *locationlist[30];
	// Fixed Array size - We don't always know this
};

// Function for adding a map
struct Map *addMap(int numlocations){
	// Allocate memory for map
	struct Map *map = malloc(sizeof(struct Map));

	// Allocate memory for locations
	struct LocationNode *locationlist = malloc(sizeof(numlocations * sizeof(struct LocationNode)));

	map -> numlocations = numlocations;
	// Add locations on the map
	for (int u=0; u < map->numlocations; u++){
		// create location node with given id
		struct LocationNode *location = addLocation(u);
		map -> locationlist[u] = location;
	};

	return map;
};

void addNeighbor(struct Map *map, int sourceloc, int destloc){
	// We will add neighbors at the beginning of the linked lists
	// Explore the effect of changing this insertion order
	struct LocationNode *newlocation = addLocation(destloc);
	newlocation -> neighbor = map -> locationlist[sourceloc];
	map -> locationlist[sourceloc] = newlocation;
	return newlocation;
}

int main(){
	// Create a map
	struct Map *map = addMap(30);
	// 30 for the locations in our Romania input
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

	for (int u = 0; u < 30; u++) {
		// printf("%d ->", map -> locationlist[u]->locationid) + 1;

		// Print the graph by traversing it using temp variable
		struct LocationNode *temp = map -> locationlist[u];

		while(temp != NULL){
			printf("%d -> ", temp -> locationid + 1);
			temp = temp -> neighbor;
		}

		printf("\n");
	};
	// printf(map);
	return 0;
}

/* NOTES

The graph in this code is implemented according to the
defintion in Cormen, Introduction to Algorithms
Third Edition Chapter 22.1

To model the problem with 'correct' wording the following
notations are used
G - Map
V - numlocations
v - LocationNode
Adj - locationlist
Adj[u] - locationlist[u]

*/