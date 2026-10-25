#include "generic_dslist.h"
#include <stdlib.h>
int main()
{
    //创建容器
    HEAD *head=GS_containercreate(LIST);
    //压栈
    for (size_t i = 0; i < 4; i++)
    {
        char *x=malloc(3);
        x[0]='a'+i;
        x[1]='\0';
        GS_liststackpush(head,x);
    }

    size_t n=GS_liststacksize(head);
    printf("%d\n",n);
    //出栈
    for (size_t i = 0; i < 2; i++)
    {
        char *y=GS_liststackpop(head);
        printf("%s\n",y);
        free(y);
    }
    //查看栈大小
    n=GS_liststacksize(head);
    printf("%d\n",n);
    //查看栈顶
    char *y=GS_liststacktop(head);
    printf("%s\n",y);
    //非空栈检测
    int m=GS_liststackempty(head);
    if (m==0)
    {
        printf("not empty\n");
    }
    if (m==1)
    {
        printf("empty\n");
    }
    //置空栈
    for (size_t i = 0; i < 2; i++)
    {
        char *y=GS_liststackpop(head);
        printf("%s\n",y);
        free(y);
    }
    //空栈检测
    m=GS_liststackempty(head);
    if (m==0)
    {
        printf("not empty\n");
    }
    if (m==1)
    {
        printf("empty\n");
    }
    //销毁容器
    GS_liststackdestroy(&head,free);
    m=GS_liststackempty(head);
    if (m==0)
    {
        printf("not empty\n");
    }
    if (m==1)
    {
        printf("empty\n");
    }    
    
    
}


/*测试结果：

    4
    d
    c
    2
    b
    not empty
    b
    a
    empty
    empty

*/