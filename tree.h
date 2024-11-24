//
// Created by Matth on 20/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"
#include "loc.h"
#include "map.h"

/*typedef struct s_node{
    int cost;  //cout du déplacement
    int totalcost; // utile si égalité de chemins
    int depth;
    //t_localisation loc; // regroupe orientation et position
    //struct s_node * prev;
    struct t_node ** sons;   //taille du tableau 9-depth
    int nbsons;
    int phys_sons;
    //t_move * tableau; //avec les mvts restants taille du tableau 9-depth
} t_node;*/

typedef struct s_tree{
    t_node* root;
    int max_depth;
    t_localisation start_loc;
} t_tree;


t_tree *createTree(t_node *node, int max_depth, t_localisation start_loc);
void populateRoot(t_node *root, int nb_moves, t_move *moves_list, t_map map);
void populateTree(t_tree *tree, int nb_moves, t_move *moves_list, t_map map);
void displayRoot(t_node root);

#endif //UNTITLED1_TREE_H