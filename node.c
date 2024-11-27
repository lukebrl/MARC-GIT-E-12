//
// Created by Matth on 21/11/2024.
//
#include "node.h"
#include "loc.h"
#include <stdlib.h>
#include <stdio.h>


t_node *createNode(int cost, int nbsons) {
    t_node *new_node = malloc(sizeof(t_node));
    if (new_node == NULL) {
        printf("Error while allocating mem for node.\n");
        return new_node;
    }

    new_node->cost = cost;
    new_node->totalcost = cost;
    new_node->phy_nbsons = nbsons;
    new_node->log_nbsons = 0;
    new_node->depth = 0;
    new_node->parent = NULL;
    new_node->moves_done = createEmptyHt();
    new_node->loc = loc_init(0, 0, NORTH);

    //if node doesn't have sons
    if (nbsons <= 0) {
        new_node->sons = NULL;
        return new_node;
    }

    //allocate memory for sons
    new_node->sons = malloc(sizeof(t_node**) * nbsons);
    if (new_node->sons == NULL) {
        printf("Error while allocating mem for node sons.\n");
    }

    //set all sons to NULL
    for (int i = 0; i < nbsons; i++) {
        new_node->sons[i] = NULL;
    }

    return new_node;
}


void addSons(t_node *root, t_node *son, t_move move) {
    //check if you can still add son
    if (root->log_nbsons == root->phy_nbsons) {
        printf("You can't add more sons to this node.\n");
        return;
    }

    //update total cost, parent, moves and depth of the node
    t_cell_move *tmp = root->moves_done.head;
    while (tmp) {
        addTailHt(&son->moves_done, tmp->val);
        tmp = tmp->next;
    }
    addTailHt(&son->moves_done, move);
    free(tmp);

    son->parent = root;
    son->totalcost += root->totalcost;
    son->depth = root->depth + 1;

    //add son to the node
    root->sons[root->log_nbsons] = son;
    root->log_nbsons++;
}

void updateNodeLoc(t_node *node, t_localisation new_loc) {
    node->loc.pos.x = new_loc.pos.x;
    node->loc.pos.y = new_loc.pos.y;
    node->loc.ori = new_loc.ori;
}


void displayNode(t_node node) {
    printf("[%d, %d] | ", node.loc.pos.x, node.loc.pos.y);
    printf("cost-> %d | total cost-> %d | ", node.cost, node.totalcost);
    if (node.parent != NULL) {
        printf("parent cost -> %d\n", node.parent->cost);
    }
    else {
        printf("parent cost -> None\n");
    }

    printf("sons cost -> ");
    for(int i = 0; i < node.log_nbsons; i++) {
        printf("%d, ", node.sons[i]->cost);
    }
    printf("\n");
    displayHt(node.moves_done);
    printf("\n\n");
}

void deleteNode(t_node *node) {
    for (int i = 0; i < node->log_nbsons; i++) {
        deleteNode(node->sons[i]);
    }

    deleteHtList(&node->moves_done);
    free(node->sons);
    free(node);
    node = NULL;
}
