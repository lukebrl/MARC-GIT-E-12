//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "stack.h"

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (int *)malloc(size * sizeof(int));
    return stack;
}

/**
 * @brief Function to push a value in the stack
 * @param stack : the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *p_stack, int value)
{
    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
}

/**
 * @brief Function to pop a value from the stack
 * @param stack : the stack
 * @return the value popped
 */
int pop(t_stack *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
int top(t_stack stack)
{
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}

void shufflestack(t_stack *p_stack){
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
void printStack(t_stack t){
    int tmp_nb_elts = t.nbElts;
    for (int i = 0; i < tmp_nb_elts; i++){
        printf("%d ",pop(&t));
    }
    printf("\n");
}