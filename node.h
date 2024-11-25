//
// Created by Matth on 21/11/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "moves.h"
#include "functions.h"

typedef struct s_node {
    int cost;
    int totalcost;
    int depth;
    int phy_nbsons;
    int log_nbsons;
    struct s_node **sons;
    struct s_node *parent;
    t_ht_list moves_done;
    t_localisation loc;
} t_node;

t_node *createNode(int cost, int nbsons);
void addSons(t_node *root, t_node *son, t_move move);
void displayNode(t_node node);
void updateNodeLoc(t_node *node, t_localisation new_loc);

#endif //UNTITLED1_NODE_H
