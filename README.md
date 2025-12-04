#### Documentation

[Google Docs Documentation Link](https://docs.google.com/document/d/1D65gglaSZKm3hMtcld2k7_B2pDe-OjekMC4OwB3ELlI/edit?usp=sharing)


#### Compile and Run

DFS on Romania Map:

gcc -std=c11 -Wall -Wextra romania_dfs.c dfs.c romania_map.c map_tools.c -o romania_dfs

gcc -std=c11 -Wall -Wextra astar.c dfs.c romania_map.c map_tools.c -o astar

gcc -std=c11 -Wall -Wextra tsp_sa.c romania_map.c map_tools.c -lm -o tsp_sa

#### Open Issues

- Optionally reading data from a file


