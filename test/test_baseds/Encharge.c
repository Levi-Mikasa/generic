#include <stdio.h>
#include <Windows.h>
#include "generic_containerbase.h"
int main(){
    
    int *P=0;
    HEAD *head;
    DATA *NODE;
    head=InitEncharge();
    EnchargeSpaceset(head,8);
    NODE=head->root;
    for (int i = 0; i < 3; i++)
    {
        P=malloc(sizeof(int));
        *P=i;
        NODE->dat=P;
        NODE++;
        (*P)++;
    }
    head->feature.Array.num=4;
    NODE=(DATA*)head->root;
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n",*(int*)NODE->dat);
        NODE++;
    }
    
    free(head);


    
    
    
    system("pause");
    return 0;
}


/*
测试结果：
1
2
3

*/