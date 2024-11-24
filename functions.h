#ifndef UNTITLED1_FUNCTIONS_H
#define UNTITLED1_FUNCTIONS_H
#include "loc.h"
#include "moves.h"
#include "stack.h"
typedef struct s_node{
    int cost;  //cout du déplacement
    int totalcost; // utile si égalité de chemins
    int depth;
    t_localisation loc; // regroupe orientation et position
    struct s_node * prev;
    struct s_node ** sons;   //taille du tableau 9-depth
    int nbsons;
    t_move * tableau; //avec les mvts restants taille du tableau 9-depth
} t_node;

typedef struct s_tree{
    t_node* root;
} t_tree;

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
