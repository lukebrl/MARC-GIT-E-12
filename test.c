//
// Created by Matth on 21/11/2024.
//
#include "node.h"
#include "tree.h"
#include "map.h"
#include <stdio.h>
#include <time.h>
#include "functions.h"

#include "map.h"
#include "stack.h"
#include "functions.h"
#include "rover.h"
#include "tree.h"

#define DEAD_COST 9999
#define NB_MOVES 5
#define MAX_DEPTH 3


int test() {
    //set timer for the program
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    t_map map;
    //create the map
    #if defined(_WIN32) || defined(_WIN64)
        map = createMapFromFile("..\\maps\\big.map");
    #else
        map = createMapFromFile("../maps/test.map");
    #endif

    //create rover
    t_localisation start_loc = loc_init(2, 35, NORTH);
    t_rover *rover = createRover(start_loc);

    //create stack for all moves
    int nbs[7]={22,15,7,7,21,21,7};
    t_stack moves= createStack(100);
    for (int i=0;i<7;i++){
        for (int j=0;j<nbs[i];j++){
            push(&moves,i);
        }
    }

    //create list of 9 moves
    t_stack tmp_stack = moves;
    shufflestack(&tmp_stack);
    t_move moves_list[NB_MOVES];
    for (int i = 0; i < NB_MOVES; i++) {
        int next_move = pop(&tmp_stack);
        moves_list[i] = next_move;
    }

    //create new tree and search
    //the shortest path
    t_tree *moves_tree = createTree(MAX_DEPTH, NB_MOVES, rover->loc);
    populateTree(moves_tree, NB_MOVES, moves_list, map);
    printNTree(moves_tree);
    deleteTree(moves_tree);
}