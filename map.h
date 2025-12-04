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

#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <stddef.h>

// Linked List to represent locations and neighbors
struct LocationNode{
	int locationid; // location id - integer value representing labeled location
	struct LocationNode* neighbor; // pointer to the neighbor node / location
};

// Graph structure to represent the entire map
struct Map{
	int numlocations; // Specify number of locations in the map
	// Array of location nodes
	struct LocationNode *locationlist[30];
	// Fixed Array size - We don't always know this
};

// Function prototype for adding new locations (implementation moved to map_tools.c)
struct LocationNode *addLocation(int locationid);

#endif  // end of MAP_H