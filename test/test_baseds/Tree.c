#include<stdlib.h>
#include<stdio.h>
#include "generic_containerbase.h"
void bianli(DATADOU *trnd,int **num);
void bianli2(DATADOU *trnd);
int main(){
    int *i=malloc(sizeof(int));
    *i=0;
    char *x="R";   //右
    char *r="L";   //左
    HEAD *head=InitTree();
    DATADOU *treenode=head->root;

    RTreeAdd(head,treenode);
    LTreeAdd(head,treenode);
    treenode->dat=i;
    (*i)++;

    bianli((DATADOU*)head->root,&i);
    bianli2((DATADOU*)head->root);

    TreeDelAPI(head,x);
     bianli((DATADOU*)head->root,&i);
    bianli2((DATADOU*)head->root);
    TreeDelAPI(head,r);
    bianli((DATADOU*)head->root,&i);
    bianli2((DATADOU*)head->root);
    return 0;
}
void bianli(DATADOU *trnd,int **num)
{
    if(trnd==NULL)
    {
        return;
    }
    bianli(trnd->TRnode.Lchil,num);
    bianli(trnd->TRnode.Rchil,num);
    //printf("%d",*(int*)trnd->dat);
    trnd->dat=*num;
    (**num)++;   

}
void bianli2(DATADOU *trnd)
{
    if(trnd==NULL)
    {
        return;
    }
    bianli2(trnd->TRnode.Lchil);
    bianli2(trnd->TRnode.Rchil);
    printf("%d\n",*(int*)trnd->dat);
}




//前序遍历（根->左->右）
int preorder(DATADOU* trnd)
{
    if (trnd == NULL)
    {
        return 0;
        /* code */
    }

    trnd = trnd;   //这里是访问，递归一次访问一次
    //访问自己
    preorder(trnd->TRnode.Lchil);
    preorder(trnd->TRnode.Rchil);
    

}

//中序遍历（左->根->右）
int inorder(DATADOU* trnd)
{
    if (trnd == NULL)
    {
        return 0;
        /* code */
    }

    inorder(trnd->TRnode.Lchil);
    trnd = trnd;
    inorder(trnd->TRnode.Rchil);
    
}