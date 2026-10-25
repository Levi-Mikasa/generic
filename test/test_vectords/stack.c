#include "generic_dsvector.h"
#include <stdlib.h>
#include <stdio.h>
int main()
{
    //创建容器
    HEAD *head=GS_containercreate(VECTOR);
    //进队
    for (int i = 0; i < 10; i++)
    {
        char *x=malloc(4);
        x[0]='A'+i;
        x[1]='\0';
        GS_vectorstackpush(head,x);
    }
    size_t n=GS_vectorstacksize(head);
    printf("%d\n",n);
    //出队
    for (int i = 0; i < 7; i++)
    {
        char *y=GS_vectorstackpop(head);
        printf("%s\n",y);
    }

    for (int i = 0; i < 5; i++)
    {
        char *x=malloc(4);
        x[0]='A'+i;
        x[1]='\0';
        GS_vectorstackpush(head,x);
    }
    //队大小查看
    n=GS_vectorstacksize(head);
    printf("%d\n",n);
    //队首队尾查看
    char *t=GS_vectorstackback(head);
    printf("%s\n",t);
    t=GS_vectorstackpeek(head);
    printf("%s\n",t);
    //非空队检测
    int x=GS_vectorstackempty(head);
    if (x==1)
    {
        printf("empty\n");
    }
    if (x==0)
    {
        printf("not empty\n");
    }
    //清空队列
    for (int i = 0; i < 4; i++)
    {
        char *y=GS_vectorstackpop(head);
        printf("%s\n",y);

    }
    //空队检测
    x=GS_vectorstackempty(head);
    if (x==0)
    {
        printf("not empty\n");
    }
    if (x==1)
    {
        printf("empty\n");
    }
    GS_vectorstackdestroy(&head,free);
    x=GS_vectorstackempty(head);
    if (x==0)
    {
        printf("not empty\n");
    }
    if (x==1)
    {
        printf("empty\n");
    }
    

    
}



/*
测试结果：
    10
    J
    I
    H
    G
    F
    E
    D
    10
    A
    E
    not empty
    E
    D
    C
    B
    not empty
    empty

*/