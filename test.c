//
// Created by Matth on 21/11/2024.
//
#include "node.h"
#include "tree.h"
#include "map.h"
#include <stdio.h>
#include <time.h>

void displayMapCosts(t_map map) {
    for(int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.costs[i][j]);
        }
        printf("\n");
    }
}

int test() {



    t_map map = createMapFromFile("..\\maps\\big.map");
    displayMapCosts(map);
    displayMap(map);
    t_localisation start_loc = loc_init(1, 4, NORTH);
    t_move moves_list[] = {F_10, T_RIGHT, B_10, U_TURN, F_10};
    t_tree *tree = createTree(3, 5, start_loc);
    //timer
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    populateTree(tree, 5, moves_list, map);
    printNTree(tree);

    t_node shortest_path = findShortestPathTree(*tree);
    displayNode(shortest_path);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n****************************\n");
    printf("* time taken: %.6f sec *\n", cpu_time_used);;
    printf("****************************\n");
    return 0;
}
