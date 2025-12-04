#include <stdio.h>
#include "dfs.h"
#include "romania_map.h"

int main(void){
    struct Map *map = create_map(30);
    if (!map) return 1;

    int order[] = {0};
    DFSTraversal(map, order, 1);
    printf("\n");

    return 0;
}
