#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "map.h"
#include "stack.h"
#include "functions.h"
#include "rover.h"
#include "tree.h"

#define DEAD_COST 9999
#define NB_MOVES 9
#define MAX_DEPTH 5


int main() {
    //set timer for the program
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    t_map map;
    //create the map
    #if defined(_WIN32) || defined(_WIN64)
        map = createMapFromFile("..\\maps\\big.map");
    #else
        map = createMapFromFile("../maps/example1.map");
    #endif

    //create rover
    srand(time(NULL));
    int xdep=rand()%map.x_max,ydep=rand()%map.y_max;
    printf("Initial Rover Loc: (x :%d,y :%d)\n\n",xdep,ydep);
    t_localisation start_loc = loc_init(xdep, ydep, NORTH);
    t_rover *rover = createRover(start_loc);

    //create stack for all moves
    int nbs[7]={22,15,7,7,21,21,7};
    t_stack moves= createStack(100);
    for (int i=0;i<7;i++){
        for (int j=0;j<nbs[i];j++){
            push(&moves,i);
        }
    }

    //loop that last until rover find the base
    //or if no move remains
    //or if rover dies
    int base_found = 0;
    int dead = 0;
    int phase_number = 0;
    while(!base_found && !dead) {
        //clock to get time of each phase
        clock_t start_phase = clock();

        //create list of 9 moves
        t_stack tmp_stack = moves;
        shufflestack(&tmp_stack);
        t_move moves_list[NB_MOVES];
        for (int i = 0; i < NB_MOVES; i++){
            int next_move = pop(&tmp_stack);
            moves_list[i] = next_move;
        }

        //create new tree and search
        //the shortest path
        t_tree *moves_tree = createTree(MAX_DEPTH, NB_MOVES, rover->loc);
        populateTree(moves_tree, NB_MOVES, moves_list, map);
        //printNTree(moves_tree);

        t_node shortest_path_node = findShortestPathTree(*moves_tree);

        //update pos and add every
        //move from the path to the rover moves
        updateRoverLoc(rover, shortest_path_node.loc);
        t_cell_move *tmp = shortest_path_node.moves_done.head;
        while (tmp) {
            addRoverMove(rover, tmp->val);
            tmp = tmp->next;
        }

        clock_t end_phase = clock();
        double elapsed_time = ((double) (end_phase - start_phase)) / CLOCKS_PER_SEC;
        printf("Available moves:\n");
        printTabMovesTest(moves_list,9);
        printf("\n#####################################\n");
        printf("Phase number: %d\n", phase_number+1);
        printf("#####################################\n");
        printf("Total Execution Time:\n%f sec\n", elapsed_time);
        printf("#####################################\n");
        printf("Done Path: \n");
        displayHt(shortest_path_node.moves_done);
        printf("#####################################\n");
        printf("Rover Loc:\n [%d, %d]\n", rover->loc.pos.x, rover->loc.pos.y);
        printf("#####################################\n\n");


        if (shortest_path_node.cost >= DEAD_COST) {
            dead = 1;
        }
        else if (shortest_path_node.cost == 0) {
            base_found = 1;
        }
        //TODO: free memory for moves_list
        phase_number++;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if (dead) {
        printf("\nRover fell into a crevasse or went OOB.\n");
    }
    else if (base_found) {
        printf("\n\n\n#####################################\n");
        printf("Path to the base: \n");
        displayHt(rover->moves_done);
        printf("#####################################\n");
        printf("Number Of Execution:\n%d \n", phase_number);
        printf("#####################################\n");
        printf("Total Execution Time:\n%.6f sec\n", cpu_time_used);
        printf("#####################################\n");
        printf("Final Rover Loc:\n [%d, %d]\n", rover->loc.pos.x, rover->loc.pos.y);
        printf("#####################################\n");

    }
    return 0;
}

