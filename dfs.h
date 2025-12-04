#ifndef DFS_H
#define DFS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "map.h"

/* DFS prototypes - implementations moved to dfs.c to avoid multiple definitions */
void DFS(struct Map* map, int location, bool visited[]);
void DFSTraversal(struct Map* map, int* order, int orderSize);

#endif  // DFS_H
