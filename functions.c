#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
int* createtab(int size ,int elem){
    int* tab=malloc(size*sizeof(int));
    for (int i=0;i<size;i++){
        tab[i]=elem;
    }
    return tab;
}
void printtab(int* tab, int size){
    //int k=0;
    for (int i=0;i<size;i++){
        printf("%d ",tab[i]);//k++;
    }
    //printf("       %d",k); verif pour voir si c'etait les bonnes tailles
    printf("\n");
}
int isEmptyStack(t_stack t){
    if (t.nbElts==0){
        return 1;
    }
    return 0;
}
int countstack(t_stack t,int val){
    int cpt=0;
    while (!isEmptyStack(t)){
        if (pop(&t)==val) {
            cpt++;
        }
    }
    return cpt;
}
void printTabMoves(int* tab, int size){
    for (int i=0;i<size;i++){
        printf("%s, ",getMoveAsString(tab[i]));
    }
    printf("\n");
}


t_test createStackTest(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_test stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (int *)malloc(size * sizeof(int));
    return stack;
}
void pushTest(t_test *p_stack, int value)
{
    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
    return;
}
t_move popTest(t_test *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}
void shufllestackTest(t_test *p_stack){
    srand(time(NULL));
    int* tmp=malloc(sizeof(int)*p_stack->size);
    for (int i=0;i<=p_stack->nbElts;i++){
        tmp[i]=p_stack->values[i];
    }
    for (int i=p_stack->nbElts-1;i>0;i--){
        int j=rand()%(i+1);
        int caca=tmp[i];
        tmp[i]=tmp[j];
        tmp[j]=caca;
    }
    for (int i=0;i<=p_stack->nbElts;i++){
        p_stack->values[i]=tmp[i];
    }
    free(tmp);
}
void printTabMovesTest(t_move* tab, int size){
    for (int i=0;i<size;i++){
        printf("%s, ",getMoveAsString(tab[i]));
    }
    printf("\n");
}
