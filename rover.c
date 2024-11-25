//
// Created by Matth on 25/11/2024.
//
#include "rover.h"
#include "loc.h"
#include <stdio.h>
#include <stdlib.h>

t_rover *createRover(t_localisation loc) {
    t_rover *rover = malloc(sizeof(t_rover));
    rover->loc = loc;
    rover->moves_done = createEmptyHt();

    return rover;
}

void updateRoverLoc(t_rover *rover, t_localisation new_loc) {
    rover->loc = new_loc;
}

void addRoverMove(t_rover *rover, t_move move) {
    addTailHt(&rover->moves_done, move);
}