#include "generic_dslist.h"
#include <stdlib.h>
int main()
{
    //创建容器
    HEAD *head=GS_containercreate(LIST);
    //进队
    for (int i = 0; i < 4; i++)
    {
        char *x=malloc(4);
        x[0]='A'+i;
        x[1]='\0';
        GS_listqueuepush(head,x);
    }
    size_t n=GS_listqueuesize(head);   //自动扩容
    printf("%d\n",n);                 //打印容器容量
    //出队
    for (int i = 0; i < 2; i++)
    {
        char *y=GS_listqueuepop(head);    //自动缩容
        printf("%s\n",y);
        free(y);
    }
    //队大小查看
    n=GS_listqueuesize(head);
    printf("%d\n",n);
    //队首队尾查看
    char *t=GS_listqueueback(head);
    printf("%s\n",t);
    t=GS_listqueuepeek(head);
    printf("%s\n",t);
    //非空队检测
    int x=GS_listqueueempty(head);
    if (x==1)
    {
        printf("empty\n");
    }
    if (x==0)
    {
        printf("not empty\n");
    }
    //清空队列
    for (int i = 0; i < 2; i++)
    {
        char *y=GS_listqueuepop(head);
        printf("%s\n",y);
        free(y);
    }
    //空队检测
    x=GS_listqueueempty(head);
    if (x==0)
    {
        printf("not empty\n");
    }
    if (x==1)
    {
        printf("empty\n");
    }
    GS_liststackdestroy(&head,free);
    x=GS_listqueueempty(head);
    if (x==0)
    {
        printf("not empty\n");
    }
    if (x==1)
    {
        printf("empty\n");
    }
    

    
}



/*测试结果：
    4
    A
    B
    2
    C
    D
    not empty
    C
    D
    empty
    empty


*/