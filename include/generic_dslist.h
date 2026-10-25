#ifndef TOOLAPI_H
#define TOOLAPI_H
#define GS_liststackdestroy GS_listdestroy
#define GS_listqueuedestroy GS_listdestroy
#define GS_liststackempty GS_listcontainerempty
#define GS_listqueueempty GS_listcontainerempty
#define GS_liststacksize GS_listsize
#define GS_listqueuesize GS_listsize
#include<stdio.h>
#include"generic_containerbase.h"






// 容器大小
size_t GS_listsize(HEAD *head);

// 压栈：支持多种类型，用双向链表
void GS_liststackpush(HEAD *head, void *dat);

// 弹栈（返回节点，用完需调用 GS_nodefree）
void *GS_liststackpop(HEAD *head);

// 查看栈顶
void *GS_liststacktop(HEAD *head);

//销单链表（栈，队列）
void GS_listdestroy(HEAD **head,GS_datadestroy des);

//进队
void GS_listqueuepush(HEAD *head,void *dat);

//出队
void *GS_listqueuepop(HEAD *head);

//查看队首（刚入队）
void *GS_listqueuepeek(HEAD *head);

//查看队尾（准备出队）
void *GS_listqueueback(HEAD *head);

//判断容器是否为空
int GS_listcontainerempty(HEAD *head);

//链表数据插入
void GS_listpush(HEAD *head,void *dat,size_t local);

//链表数据输出
void *GS_listpop(HEAD *head,size_t local);

//链表数据修改
void GS_listmodify(HEAD *head,void *dat,size_t local,GS_datadestroy des);











#endif