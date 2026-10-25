#include <stdio.h>
#include <Windows.h>
#include "generic_containerbase.h"
int main(){
    
    int *P=0;
    HEAD *head;
    DATA *NODE;
    head=InitList();
    
    for (int i = 0; i < 4; i++)
    {
        P=malloc(sizeof(int));
        *P=i;
        ListAdd(head,HEAD_ADD);
        NODE=head->root;
        NODE->dat=P;
    
        (*P)++;
    }
    head->feature.Array.num=4;
    

    NODE=(DATA*)head->root;
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n",*(int*)NODE->dat);
        NODE = NODE->NEXT;
    }
    
    free(head);


    
    
    
    system("pause");
    return 0;
}