//
// Created by Matth on 25/11/2024.
//

#ifndef UNTITLED1_ROVER_H
#define UNTITLED1_ROVER_H

#include "loc.h"
#include "functions.h"

typedef struct s_rover {
    t_localisation loc;
    t_ht_list moves_done;
} t_rover;


t_rover *createRover(t_localisation loc);
void updateRoverLoc(t_rover *rover, t_localisation new_loc);
void addRoverMove(t_rover *rover, t_move move);


#endif //UNTITLED1_ROVER_H
