//
// Created by Matth on 21/11/2024.
//
#include "node.h"
#include "tree.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

void displayMapCosts(t_map map) {
    for(int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.costs[i][j]);
        }
        printf("\n");
    }
}

int main() {

    t_map map = createMapFromFile("..\\maps\\test.map");
    displayMapCosts(map);
    displayMap(map);
    t_localisation start_loc = loc_init(2, 0, EAST);
    t_move moves_list[] = {F_10, T_RIGHT, F_30};
    t_node *root = createNode(0, 3);
    t_tree *tree = createTree(root, 3, start_loc);
    populateTree(tree, 3, moves_list, map);
    //displayRoot(*root);
    bool flag[] = {true, true, true};
    printNTree(tree->root, flag, 0, false);

    t_node shortest_path = findShortestPath(*tree->root);
    displayNode(shortest_path);


    /*t_node *list_node[5] = {node1, node2, node3, node4, node5};
    for (int i=0; i < 5; i++) {
        displayNode(*list_node[i]);
    }*/

    return 0;
}
