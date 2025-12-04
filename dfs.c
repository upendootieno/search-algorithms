#include "dfs.h"

void DFS(struct Map* map, int location, bool visited[]) {
    visited[location] = true;
    printf("%d ", location);

    struct LocationNode* currentNode = map->locationlist[location];
    while (currentNode) {
        int adjacentVertex = currentNode->locationid;
        if (!visited[adjacentVertex]) {
            DFS(map, adjacentVertex, visited);
        }
        currentNode = currentNode->neighbor; // Go to next location
    }
}

void DFSTraversal(struct Map* map, int* order, int orderSize) {
    bool* visited = (bool*)malloc(map->numlocations * sizeof(bool));
    if (!visited) return;
    for (int i = 0; i < map->numlocations; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < orderSize; i++) {
        if (!visited[order[i]]) {
            DFS(map, order[i], visited);
        }
    }

    free(visited);
}
