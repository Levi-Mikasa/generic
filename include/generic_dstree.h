#ifndef GENERIC_DSTREE_H
#define GENERIC_DSTREE_H
#include <generic_containerbase.h>

// 按照层序插入单个节点，构建完全二叉树
int TreeCompleteInsert(HEAD* head, void* dat);

// 按指定遍历顺序读取节点数据
void* TreeDataRead(HEAD* head,size_t index,TREE_ORDER order);

// 按指定遍历顺序改写节点数据
int TreeDataWrite(HEAD* head,size_t index,TREE_ORDER order,void* dat);

// 通过路径寻址找到节点删除子树
void TreeDataDelAPIbyPath(HEAD *head,char *Aim,GS_datadestroy destroy);

// 通过定序寻址找到节点删除子树
void TreeDataDelAPIbyOrder(HEAD *head,TREE_ORDER order,size_t index,GS_datadestroy destroy);

#endif