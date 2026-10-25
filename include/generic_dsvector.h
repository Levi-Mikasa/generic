#ifndef GENERIC_DSVECTOR_H
#define GENERIC_DSVECTOR_H
#define GS_vectorqueuesize GS_vectorsize
#define GS_vectorstacksize GS_vectorsize
#define GS_vectorstackempty GS_vectorcontainerempty
#define GS_vectorqueueempty GS_vectorcontainerempty
#define GS_vectorstackdestroy GS_vectordestroy
#define GS_vectorqueuedestroy GS_vectordestroy
#include "generic_containerbase.h"
//容器大小
size_t GS_vectorsize(HEAD* head);
//推栈
void GS_vectorstackpush(HEAD* head,void* data);
//弹栈
void* GS_vectorstackpop(HEAD* head);

//查看栈顶（刚入栈）
void *GS_vectorstackpeek(HEAD *head);
//查看栈底（准备出队）
void *GS_vectorstackback(HEAD *head);

//进队
void* GS_vectorqueuepush(HEAD* head,void* data);
//出队
void* GS_vectorqueuepop(HEAD* head);

//查看队首（刚入队）
void *GS_vectorqueuepeek(HEAD *head);
//查看队尾（准备出队）
void *GS_vectorqueueback(HEAD *head);

//可变数组判空（为空就是true）
int GS_vectorcontainerempty(HEAD *head);

//销毁数据结构
void GS_vectordestroy(HEAD **head,GS_datadestroy des);


#endif