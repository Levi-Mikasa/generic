#include "generic_dslist.h"
#include <stdio.h>
#include <stdlib.h>


size_t GS_listsize(HEAD *head)
{
    return head->size;
}

void GS_liststackpush(HEAD *head, void *dat)
{
    ListAdd(head,TAIL_ADD);
    DATA *NODE=head->feature.Lists.ListType.LastNode;
    NODE->dat=dat;
}

void *GS_liststackpop(HEAD *head)
{
    if(head==NULL||head->root==NULL)
    {
        return NULL;
    }
    void *dat;
    dat=head->feature.Lists.ListType.LastNode->dat;

    ListDel(head,head->size);

    return dat;
}

void *GS_liststacktop(HEAD *head)
{
    return head->feature.Lists.ListType.LastNode->dat;
}

void GS_listqueuepush(HEAD *head,void *dat)
{
    ListAdd(head,HEAD_ADD);
    DATA *NODE=head->root;
    NODE->dat=dat;

}

void *GS_listqueuepop(HEAD *head)
{
    if(head==NULL||head->root==NULL)
    {
        return NULL;
    }
    DATA *dat;
    dat=head->feature.Lists.ListType.LastNode->dat;

    ListDel(head,head->size);
    return dat;
}

void *GS_listqueuepeek(HEAD *head)
{
    DATA *NODE=head->root;
    return NODE->dat;
}

void *GS_listqueueback(HEAD *head)
{
    return head->feature.Lists.ListType.LastNode->dat;
}





void GS_listdestroy(HEAD **head,GS_datadestroy des)
{
    if(head == NULL||*head ==NULL)
    {
        return;
    }

    DATA *node = (*head)->root;

    while(node != NULL)
    {
        DATA *next = node->NEXT;
        des(node->dat);
        free(node);
        
        node = next;
    }

    free(*head);
    *head=NULL;
}

int GS_listcontainerempty(HEAD *head)
{
    return head == NULL || head->root == NULL;
}

void GS_listpush(HEAD *head,void *dat,size_t local)
{
    if (head->type != LIST||local>head->size)
    {
        return;
    }
    if (local==head->size)
    {
        ListAdd(head,TAIL_ADD);
        head->feature.Lists.ListType.LastNode->dat=dat;
        return;
    }
    if (local==0)
    {
        ListAdd(head,HEAD_ADD);
        DATA *NODE=head->root;
        NODE->dat=dat;
        return;
    }
    DATA *pre,*aft;
    DATA *NODE=malloc(sizeof(DATA));
    NODE->dat=dat;
    pre=head->root;
    aft=head->root;
    for (size_t i = 0; i < local; i++)
    {
        aft=aft->NEXT;
        if (i+1!=local)
        {
            pre=pre->NEXT;
        }
        
    }
    pre->NEXT=NODE;
    NODE->NEXT=aft; 
    
}

//链表数据输出
void *GS_listpop(HEAD *head,size_t local)
{
    if (head->type != LIST||local>head->size)
    {
        return NULL;
    }
    void *dat;
    DATA *NODE=head->root;
    for (size_t i = 0; i < local; i++)
    {
        NODE=NODE->NEXT;
    }
    dat=NODE->dat;
    ListDel(head,local);
    return dat;
}

//链表数据修改
void GS_listmodify(HEAD *head,void *dat,size_t local,GS_datadestroy des)
{
    if (head->type != LIST||local>head->size)
    {
        return;
    }
    DATA *NODE=listsearch(head,local);
    if (NODE->dat !=NULL)
    {
        des(NODE->dat);
    }
    NODE->dat=dat;
    
}

