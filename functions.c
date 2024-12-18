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
    stack.values = (t_move *)malloc(size * sizeof(t_move));
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



void addTailHt(t_ht_list * list, t_move val){
    t_cell_move * newc=createCell(val);
    if(isEmptyHtList(*list)){
        list->head=newc;
        list->tail=newc;
        return;
    }
    list->tail->next=newc;
    list->tail=newc;
}
int isEmptyHtList(t_ht_list list){
    if((list.head==NULL)&&(list.tail==NULL)){
        return 1;
    }
    return 0;
}
t_cell_move *createCell(t_move val){
    t_cell_move *newcell=malloc(sizeof(t_cell_move));
    newcell->val=val;
    newcell->next=NULL;
    return newcell;
}

void deleteCell(t_cell_move *cell) {
    free(cell);
    cell = NULL;
}

t_ht_list createEmptyHt(){
    t_ht_list list;
    list.head=NULL;
    list.tail=NULL;
    return list;
}

void displayHt(t_ht_list list) {
    t_cell_move *tmp = list.head;
    while(tmp){
        printf("%s, ", getMoveAsString(tmp->val));
        tmp=tmp->next;
    }
    printf("\n");
}

void deleteHtList(t_ht_list *list) {
    t_cell_move *start = list->head;
    while (start) {
        t_cell_move* temp = start;
        start = start -> next;
        deleteCell(temp);
    }
    list = NULL;
}