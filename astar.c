#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "romania_map.h"
#include "map_tools.h"

/* Simple A* implementation for an unweighted graph. Heuristic is zero for all
   nodes (i.e., A* behaves like BFS / uniform-cost search). This is kept
   straightforward for the demonstration using the Romania map. */

static int pop_min_index(int *openSet, int openSize, int *fscore){
    int bestIdx = -1;
    int bestF = INT_MAX;
    for (int i = 0; i < openSize; ++i){
        int v = openSet[i];
        if (fscore[v] < bestF){
            bestF = fscore[v];
            bestIdx = i;
        }
    }
    if (bestIdx == -1) return -1;
    int val = openSet[bestIdx];
    /* remove from openSet by shifting */
    for (int i = bestIdx; i+1 < openSize; ++i) openSet[i] = openSet[i+1];
    return val;
}

void astar_search(struct Map *map, int start, int goal){
    int n = map->numlocations;
    int *cameFrom = calloc(n, sizeof(int));
    int *gscore = malloc(n * sizeof(int));
    int *fscore = malloc(n * sizeof(int));
    bool *inOpen = calloc(n, sizeof(bool));

    for (int i=0;i<n;i++){
        gscore[i] = INT_MAX/4;
        fscore[i] = INT_MAX/4;
        cameFrom[i] = -1;
    }

    int *openSet = malloc(n * sizeof(int));
    int openSize = 0;

    gscore[start] = 0;
    fscore[start] = 0; /* heuristic = 0 */
    openSet[openSize++] = start;
    inOpen[start] = true;

    while (openSize > 0){
        int current = pop_min_index(openSet, openSize, fscore);
        /* rebuild inOpen and openSet representation */
        openSize = 0; for (int i=0;i<n;i++) if (inOpen[i]) openSet[openSize++]=i;

        if (current == goal) break;

        inOpen[current] = false;

        struct LocationNode *nbr = map->locationlist[current];
        while (nbr){
            int neighbor = nbr->locationid;
            int tentative_g = gscore[current] + 1; /* edge weight = 1 */
            if (tentative_g < gscore[neighbor]){
                cameFrom[neighbor] = current;
                gscore[neighbor] = tentative_g;
                fscore[neighbor] = tentative_g; /* + heuristic( neighbor ) = 0 */
                if (!inOpen[neighbor]){
                    inOpen[neighbor] = true;
                    openSet[openSize++] = neighbor;
                }
            }
            nbr = nbr->neighbor;
        }
    }

    if (cameFrom[goal] == -1 && start != goal){
        printf("No path found from %d to %d\n", start, goal);
    } else {
        /* reconstruct path */
        int stackSize = 0;
        int *stack = malloc(n * sizeof(int));
        int cur = goal;
        while (cur != -1){
            stack[stackSize++] = cur;
            if (cur == start) break;
            cur = cameFrom[cur];
        }
        for (int i = stackSize-1; i>=0; --i){
            printf("%d%s", stack[i], i?" -> ":"\n");
        }
        free(stack);
    }

    free(cameFrom);
    free(gscore);
    free(fscore);
    free(inOpen);
    free(openSet);
}

int main(void){
    struct Map *map = create_map(30);
    if (!map) return 1;

    /* Example: find path from 0 to 11 (there is a small graph connectivity in sample) */
    printf("A* path from 0 to 11:\n");
    astar_search(map, 0, 11);

    return 0;
}
