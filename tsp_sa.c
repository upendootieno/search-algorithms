#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "romania_map.h"
#include "map_tools.h"

/*
 Simple TSP solver using simulated annealing. The cost between two nodes
 is computed as the unweighted shortest-path distance (BFS) on the Romania
 map. For demonstration we consider cities 0..9 (as present in the sample map).
*/

static void bfs_distances(struct Map *map, int src, int *dist){
    int n = map->numlocations;
    for (int i=0;i<n;i++) dist[i] = -1;
    int *queue = malloc(n * sizeof(int));
    int qh=0, qt=0;
    queue[qt++] = src;
    dist[src]=0;
    while (qh<qt){
        int v = queue[qh++];
        struct LocationNode *nbr = map->locationlist[v];
        while (nbr){
            int u = nbr->locationid;
            if (dist[u]==-1){
                dist[u] = dist[v]+1;
                queue[qt++] = u;
            }
            nbr = nbr->neighbor;
        }
    }
    free(queue);
}

static int total_length(int *order, int m, int **dist){
    int sum = 0;
    for (int i=0;i<m-1;i++){
        int d = dist[order[i]][order[i+1]];
        if (d<0) return INT_MAX/4; // disconnected
        sum += d;
    }
    // return to start (make it a tour)
    int d = dist[order[m-1]][order[0]];
    if (d<0) return INT_MAX/4;
    sum += d;
    return sum;
}

int main(void){
    struct Map *map = create_map(30);
    if (!map) return 1;

    int cities = 10; // 0..9
    int n = map->numlocations;

    // Precompute distances between all nodes (we only need 0..9 rows)
    int **dist = malloc(n * sizeof(int*));
    for (int i=0;i<n;i++){
        dist[i] = malloc(n * sizeof(int));
        bfs_distances(map, i, dist[i]);
    }

    int *order = malloc(cities * sizeof(int));
    for (int i=0;i<cities;i++) order[i]=i;

    srand((unsigned)time(NULL));

    int current_cost = total_length(order, cities, dist);

    double T = 1000.0;
    double Tmin = 1e-3;
    double alpha = 0.995;

    int *best = malloc(cities * sizeof(int));
    for (int i=0;i<cities;i++) best[i]=order[i];
    int best_cost = current_cost;

    while (T > Tmin){
        // propose neighbor: swap two cities
        int i = rand()%cities;
        int j = rand()%cities;
        if (i==j) continue;
        // swap
        int tmp = order[i]; order[i]=order[j]; order[j]=tmp;

        int new_cost = total_length(order, cities, dist);
        int delta = new_cost - current_cost;
        if (delta < 0 || exp(-delta / T) > (double)rand() / RAND_MAX){
            current_cost = new_cost;
            if (current_cost < best_cost){
                best_cost = current_cost;
                for (int k=0;k<cities;k++) best[k]=order[k];
            }
        } else {
            // revert
            tmp = order[i]; order[i]=order[j]; order[j]=tmp;
        }

        T *= alpha;
    }

    printf("Simulated Annealing TSP over nodes 0..%d\n", cities-1);
    printf("Best cost: %d\nPath: ", best_cost);
    for (int i=0;i<cities;i++) printf("%d%s", best[i], i==cities-1?"\n":" -> ");

    for (int i=0;i<n;i++) free(dist[i]);
    free(dist);
    free(order);
    free(best);

    return 0;
}
