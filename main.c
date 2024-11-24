#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "stack.h"
#include "functions.h"
#include <unistd.h>
int main() {
    t_map map = createMapFromFile("/Users/macos/CLionProjects/MARC-master/maps/example1.map");
    int nbs[7]={22,15,7,7,21,21,7};
    int tab[9];
    t_stack mooves= createStack(100);
    for (int i=0;i<7;i++){
        for (int j=0;j<nbs[i];j++){
            push(&mooves,i);
        }
    }
    //printstack(mooves);
    shufllestack(&mooves);
    //printstack(mooves);
    for(int i=0;i<9;i++){
        tab[i]= pop(&mooves);
    }

    printtab(tab,9);
    printTabMoves(tab,9);

    t_move tab2[9];
    t_test moves2= createStackTest(100);
    for (int i=0;i<7;i++){
        for (int j=0;j<nbs[i];j++){
            pushTest(&moves2,i);
        }
    }
    //sleep(3); //montre que les deux stacks sont differentes
    shufllestackTest(&moves2);
    for(int i=0;i<9;i++){
        tab2[i] = popTest(&moves2);
    }
    printTabMovesTest(tab2,9);
    t_ht_list list=createEmptyHt();
    for (int i=0;i<9;i++){
        addTailHt(&list,tab2[i]);
    }
    t_cell_move *tmp=list.head;
    int a=0;
    while(tmp){
        printf("%s, ", getMoveAsString(tab2[a++]));
        tmp=tmp->next;
    }





    /**
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);**/
    return 0;
}

