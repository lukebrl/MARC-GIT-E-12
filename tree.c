#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
//
// Created by Matth on 20/11/2024.
//

t_tree *createTree(t_node *node, int max_depth, t_localisation start_loc) {
    t_tree *new_tree = malloc(sizeof(t_tree));

    updateNodeLoc(node, start_loc);
    new_tree->root = node;
    new_tree->max_depth = max_depth;
    new_tree->start_loc = start_loc;

    return new_tree;

}

void populateRoot(t_node *root, int nb_moves, t_move *moves_list, t_map map) {
    //add all sons to current root
    //and add all sons sons by recursive
    for (int i = 0; i < nb_moves; i++) {

        t_localisation next_loc = move(root->actual_loc, moves_list[i]);
        //if move is invalid we stop here for this tree branch
        if (!isValidLocalisation(next_loc.pos, map.x_max, map.y_max)) {
            t_node *new_node = createNode(10000, nb_moves-1);
            updateNodeLoc(new_node, next_loc);
            addSons(root, new_node);
            continue;
        }

        //create temp moves list with current move removed
        t_move *temp_moves = removeMoveAtIndex(moves_list, nb_moves, i);
        //get cost from next location on map
        int cost = map.costs[next_loc.pos.y][next_loc.pos.x];

        //create new node and add it as a son
        t_node *new_node = createNode(cost, nb_moves-1);
        updateNodeLoc(new_node, next_loc);
        addSons(root, new_node);

        //stop population if nb_moves is 0
        //or if we found the base or fall in a crevasse
        if (nb_moves - 1 != 0 && cost != 0 && cost < 9999) {
            populateRoot(new_node, nb_moves - 1, temp_moves, map);
        }
        //free temp moves memory
        deleteMovesList(temp_moves);
    }
}

//wrapper for tree
void populateTree(t_tree *tree, int nb_moves, t_move *moves_list, t_map map) {
    populateRoot(tree->root, nb_moves, moves_list, map);
}

t_node findShortestPath(t_node root) {
    //if no son
    if (root.log_nbsons == 0) {
        return root;
    }

    //save value of the cheapest node found
    t_node cheapest_node;
    int is_defined = 0;
    //check for each sons
    for (int i = 0; i < root.log_nbsons; i++) {
        //printf("[%d] %d, sons: %d\n", i, root.sons[i]->cost, root.sons[i]->log_nbsons);
        t_node min_node = findShortestPath(*root.sons[i]);

        //if son is a leaf and not OOB
        if (root.sons[i]->log_nbsons == 0 && root.sons[i]->cost <= 9999) {
            //displayNode(min_node);
            return *root.sons[i];
        }

        //compare all sons
        if (!is_defined || (min_node.totalcost <= cheapest_node.totalcost && min_node.cost <= cheapest_node.cost)) {
            cheapest_node = min_node;
            is_defined = 1;
        }
        //displayNode(cheapest_node);
    }
    return cheapest_node;
}


void displayRoot(t_node root) {
    displayNode(root);
    for(int i=0; i < root.log_nbsons; i++) {
        displayRoot(*root.sons[i]);
    }
}



#include <stdbool.h>

void printNTree(t_node* x, bool* flag, int depth, bool isLast) {
    if (x == NULL)
        return;

    for (int i = 1; i < depth; ++i) {
        if (flag[i] == true) {
            printf("|   ");
        } else {
            printf("    ");
        }
    }

    if (depth == 0)
        printf("%d\n", x->cost);
    else if (isLast) {
        printf("+--- %d\n", x->cost);
        flag[depth] = false;
    } else {
        printf("+--- %d\n", x->cost);
    }

    for (int it = 0; it < x->log_nbsons; ++it) {
        printNTree(x->sons[it], flag, depth + 1, it == (x->log_nbsons - 1));
    }
    flag[depth] = true;
}