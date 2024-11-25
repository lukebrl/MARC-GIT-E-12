#ifndef UNTITLED1_FUNCTIONS_H
#define UNTITLED1_FUNCTIONS_H
#include "loc.h"
#include "moves.h"
#include "stack.h"

typedef struct s_cell_move{
    t_move val;
    struct s_cell_move * next;
}t_cell_move;

typedef struct s_ht_list{
    t_cell_move * head;
    t_cell_move * tail;
}t_ht_list;


void addTailHt(t_ht_list *list, t_move val);
int isEmptyHtList(t_ht_list list);
t_cell_move *createCell(t_move val);
t_ht_list createEmptyHt();
void displayHt(t_ht_list list);
void displayHtAsString(t_ht_list list);


typedef struct s_test
{
    t_move *values;
    int size;
    int nbElts;
} t_test;

t_test createStackTest(int size);
void pushTest(t_test *p_stack, int value);
t_move popTest(t_test *p_stack);
void shufllestackTest(t_test *p_stack);
void printTabMovesTest(t_move* tab, int size);


int* createtab(int size,int elem);
void printtab(int* tab, int size);
void printTabMoves(int* tab, int size);
int countstack(t_stack t, int val);
int isEmptyStack(t_stack t);
#endif //UNTITLED1_FUNCTIONS_H

