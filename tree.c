#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
//
// Created by Matth on 20/11/2024.
//

t_tree *createTree(int max_depth, int root_nb_sons, t_localisation start_loc) {
    t_tree *new_tree = malloc(sizeof(t_tree));

    new_tree->root = createNode(0, root_nb_sons);
    updateNodeLoc(new_tree->root, start_loc);
    new_tree->max_depth = max_depth;
    new_tree->start_loc = start_loc;

    return new_tree;

}

void populateRoot(t_node *root, int max_depth, int nb_moves, t_move *moves_list, t_map map) {
    //stop if root depth is max depth
    if (root->depth == max_depth) {
        return;
    }

    //add all sons to current root
    //and add all sons sons by recursive
    for (int i = 0; i < nb_moves; i++) {

        t_localisation next_loc = move(root->loc, moves_list[i]);
        //if move is invalid we stop here for this tree branch
        if (!isValidLocalisation(next_loc.pos, map.x_max, map.y_max)) {
            t_node *new_node = createNode(10000, nb_moves-1);
            updateNodeLoc(new_node, next_loc);
            addSons(root, new_node, moves_list[i]);
            continue;
        }

        //create temp moves list with current move removed
        t_move *temp_moves = removeMoveAtIndex(moves_list, nb_moves, i);
        //get cost from next location on map
        int cost = map.costs[next_loc.pos.y][next_loc.pos.x];

        //create new node and add it as a son
        t_node *new_node = createNode(cost, nb_moves-1);
        updateNodeLoc(new_node, next_loc);
        addSons(root, new_node, moves_list[i]);

        //stop population if nb_moves is 0
        //or if we found the base or fall in a crevasse
        if (nb_moves - 1 != 0 && cost != 0 && cost < 9999) {
            populateRoot(new_node, max_depth, nb_moves - 1, temp_moves, map);
        }
        //free temp moves memory
        deleteMovesList(temp_moves);
    }
}

//wrapper for tree
void populateTree(t_tree *tree, int nb_moves, t_move *moves_list, t_map map) {
    populateRoot(tree->root, tree->max_depth, nb_moves, moves_list, map);
}

t_node findShortestPathNode(t_node root) {
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
        t_node min_node = findShortestPathNode(*root.sons[i]);

        //compare all sons
        if (!is_defined || (min_node.totalcost <= cheapest_node.totalcost && min_node.cost <= cheapest_node.cost)) {
            cheapest_node = min_node;
            is_defined = 1;
        }
        //displayNode(cheapest_node);
    }
    return cheapest_node;
}

//wrapper for tree
t_node findShortestPathTree(t_tree tree) {
    return findShortestPathNode(*tree.root);
}


void displayRoot(t_node root) {
    displayNode(root);
    for(int i=0; i < root.log_nbsons; i++) {
        displayRoot(*root.sons[i]);
    }
}



#include <stdbool.h>

void printNTreeNode(t_node* x, bool* flag, int depth, bool isLast) {
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
        printNTreeNode(x->sons[it], flag, depth + 1, it == (x->log_nbsons - 1));
    }
    flag[depth] = true;
}

void printNTree(t_tree *tree) {
    bool flag[tree->max_depth + 1];
    for (int i = 0; i < tree->max_depth; i++) {
        flag[i] = true;
    }
    printNTreeNode(tree->root, flag, 0, false);
}

void deleteTree(t_tree *tree) {
    deleteNode(tree->root);

    free(tree);
    tree = NULL;
}