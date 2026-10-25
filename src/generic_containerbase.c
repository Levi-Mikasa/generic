#include"generic_containerbase.h"
#include<stdlib.h>
#include<string.h>

//可变数组初始化
HEAD *InitEncharge()
{
    HEAD *HEAD;
    HEAD=malloc(sizeof *HEAD);
    if(HEAD == NULL)//判断是否为空
    {
        return NULL;
    }
    HEAD->type=VECTOR;
    HEAD->size=0;
    HEAD->feature.Array.num=0;
    HEAD->root=NULL;
    HEAD->feature.Array.vectorpointersignal=NULL;
    return HEAD; 
}
//可变数组空间设置
// void EnchargeSpaceset(HEAD* head,size_t capacity)
// {
//     if (head->type != VECTOR || head->feature.Array.num > capacity)
//     {
//         return;
//     }
//     DATA* data = realloc(head->root,capacity*sizeof(DATA));
//     if (data == NULL)
//     {
//         return;
//     }
//     head->root = data;
//     head->size = capacity;

//     return;
    
// }

void EnchargeSpaceset(HEAD* head, size_t capacity)
{
    if (head == NULL ||
        head->type != VECTOR ||
        head->feature.Array.num > capacity ||
        capacity > SIZE_MAX / sizeof(DATA))
    {
        return;
    }

    size_t oldsize = head->size;

    DATA* data = realloc(head->root, capacity * sizeof(DATA));

    if (data == NULL && capacity != 0)
    {
        return;
    }

    head->root = data;
    head->size = capacity;

    // 只初始化新增的空间
    if (capacity > oldsize)
    {
        for (size_t i = oldsize; i < capacity; i++)
        {
            data[i].dat = NULL;
        }
    }

    return;
}

HEAD *InitList()
{
    HEAD *HEAD;
    HEAD = malloc(sizeof(*HEAD));
    HEAD->type = LIST;
    HEAD->size = 0;
    HEAD->feature.Lists.ListType.LastNode = NULL;
    HEAD->root = NULL;
    return HEAD;
}



void ListAdd(HEAD *HEAD,ADD_LOCAL local)
{
    if (HEAD->type!=LIST)
    {
        return;
    }
    DATA *NODE;
    if (HEAD->size==0)
    {
        NODE=malloc(sizeof(DATA));
        HEAD->root=NODE;
        HEAD->size=1;
        HEAD->feature.Lists.ListType.LastNode=NODE;
        NODE->dat=NULL;
        NODE->NEXT=NULL;
        return;
    }
    switch (local)
    {
        case TAIL_ADD:
            NODE=malloc(sizeof(DATA));
            NODE->dat=NULL;
            NODE->NEXT=NULL;
            HEAD->feature.Lists.ListType.LastNode->NEXT=NODE;
            HEAD->feature.Lists.ListType.LastNode=NODE;  
            HEAD->size++;
            break;
        
        case HEAD_ADD:
            NODE=malloc(sizeof(DATA));
            NODE->dat=NULL;
            NODE->NEXT=HEAD->root;
            HEAD->root=NODE;
            HEAD->size++;
            break;

        default:
            break;
        
    }
    

}

void ListDel(HEAD *HEAD,int num)  //单链表节点删除 输入头节点和删除第几个节点
{
    if (HEAD->type!=LIST||HEAD->root == NULL)//或：有一个条件达成
    {
        return;
    }
    DATA *NODE1,*NODE2;
    NODE1=HEAD->root;
    if (num == 1)
    {
        HEAD->root=NODE1->NEXT;
        free(NODE1);
        HEAD->size--;
        return;
    }
    
    for (int i = 1; i < num-1; i++)
    {
        if (NODE1->NEXT==NULL)
        {
            return;
        }
        
        NODE1=NODE1->NEXT;
    }
    if(num==HEAD->size)
    {
        HEAD->feature.Lists.ListType.LastNode=NODE1;
        free(NODE1->NEXT);
        NODE1->NEXT=NULL;
        HEAD->size--;
        return;
    }
    NODE2=NODE1->NEXT;
    NODE1->NEXT=NODE2->NEXT;
    free(NODE2);
    HEAD->size--;
    
    
}

//链表数据查找
DATA *listsearch(HEAD *head,size_t local)
{
    if (local>head->size)
    {
        return NULL;
    }
    
    DATA *NODE=head->root;
    for (size_t i = 0; i < local; i++)
    {
        NODE=NODE->NEXT;
    }
    return NODE;
    
}

HEAD *InitDouList()
{
    HEAD *HEAD;
    HEAD=malloc(sizeof(*HEAD));
    HEAD->type=LIST;
    HEAD->size=0;
    HEAD->feature.Lists.ListType.DouLastNode=NULL;
    return HEAD;
}


void DoublyListAdd(HEAD *HEAD)
{
    if (HEAD->type != DOULIST)
    {
        return;
    }
    
    if (HEAD->size==0)
    {
        DATADOU *NODE=malloc(sizeof(*NODE));
        HEAD->root=NODE;
        NODE->LInode.AfNode=NULL;
        NODE->LInode.PrNode=NULL;
        NODE->dat=NULL;
        HEAD->feature.Lists.ListType.DouLastNode=NODE;
        HEAD->size++;
        return;
    }
    DATADOU *NODE =malloc(sizeof(*NODE));
    HEAD->feature.Lists.ListType.DouLastNode->LInode.AfNode=NODE;
    NODE->LInode.PrNode=HEAD->feature.Lists.ListType.DouLastNode;
    NODE->dat=NULL;
    NODE->LInode.AfNode=NULL;
    HEAD->size++;
    HEAD->feature.Lists.ListType.DouLastNode=NODE;
}

void DoublyListDel(HEAD *HEAD,int num)
{
    if (HEAD->type!=DOULIST)
    {
        return;
    }
    DATADOU *NODE;
    if (num ==1) //删头
    {
        NODE=HEAD->root;
        if (NODE->LInode.AfNode==NULL)
        {
            free(NODE);
            HEAD->root=NULL;
            HEAD->feature.Lists.ListType.DouLastNode=NULL;
            HEAD->size--;
            return;
        }
        
        HEAD->root=NODE->LInode.AfNode;
        NODE->LInode.AfNode->LInode.PrNode=NULL;
        free(NODE);
        HEAD->size--;
        return;
    }
    if (num == HEAD->size)  //删尾
    {
        NODE=HEAD->feature.Lists.ListType.DouLastNode->LInode.PrNode;
        free(NODE->LInode.AfNode);
        HEAD->feature.Lists.ListType.DouLastNode=NODE;
        NODE->LInode.AfNode=NULL;
        HEAD->size--;
        return;
    }
    
    if (HEAD->size-num>=HEAD->size/2)  //删中间
    {
        NODE=HEAD->root;
        for (int i = 1; i < num; i++)
        {
            NODE=NODE->LInode.AfNode;
        }
        
        
    }else{
        NODE=HEAD->feature.Lists.ListType.DouLastNode;
        for (int i = HEAD->size; i > num; i--)
        {
            NODE=NODE->LInode.PrNode;
        }
        
    }
    NODE->LInode.AfNode->LInode.PrNode=NODE->LInode.PrNode;
    NODE->LInode.PrNode->LInode.AfNode=NODE->LInode.AfNode;
    HEAD->size--;
    free(NODE);
    
}

HEAD *InitTree()
{
    HEAD *HEAD;
    HEAD=malloc(sizeof(*HEAD));
    HEAD->type=TREE;
    HEAD->feature.Trees.deepth=0;
    HEAD->size = 0;
    DATADOU *NODE=malloc(sizeof(*NODE));
    HEAD->root=NODE;
    NODE->dat=NULL;
    NODE->TRnode.Lchil=NULL;
    NODE->TRnode.Rchil=NULL;
    //HEAD->root=NODE;
    return HEAD;
}

// 寻址（依靠R，L字符串进行寻址）
DATADOU **TREEFindbyPath(char *Aim,DATADOU **NODE)
{
    while (*Aim!='\0')
    {
        if(*Aim!='R'&&*Aim!='L'|| NODE==NULL)
        {
            return NULL;
        }
        if (*Aim == 'R')
        {
            NODE=&((*NODE)->TRnode.Rchil);
        }
        if (*Aim == 'L')
        {
            NODE=&((*NODE)->TRnode.Lchil);
        }
        Aim++;
        
    }
    return NODE;
}

//前序遍历寻址（根->左->右）
static DATADOU** TreeFindPreOrder(DATADOU** node, size_t* index)
{
    if (node == NULL || *node == NULL)
    {
        return NULL;
    }



    // 目标节点已找到
    if (*index == 0)
    {
        return node;
    }

    // 访问当前节点，倒计数
    (*index)--;

    // 寻找左子树
    DATADOU** result = TreeFindPreOrder(&((*node)->TRnode.Lchil), index);
    if (result != NULL)
    {
        return result;
    }

    // 寻找右子树
    return TreeFindPreOrder(&((*node)->TRnode.Rchil), index);
}

//中序遍历寻址（左->根->右）
static DATADOU** TreeFindInOrder(DATADOU** node, size_t* index)
{
    if (node == NULL || *node == NULL)
    {
        return NULL;
    }

    // 先寻找左子树
    DATADOU** result = TreeFindInOrder(&((*node)->TRnode.Lchil), index);
    if (result != NULL)
    {
        return result;
    }

    

    // 目标节点已找到
    if (*index == 0)
    {
        return node;
    }

    // 访问当前节点，倒计数
    (*index)--;

    // 再寻找右子树
    return TreeFindInOrder(&((*node)->TRnode.Rchil), index);
}

static DATADOU** TreeFindPostOrder(DATADOU** node, size_t* index)
{
    if (node == NULL ||*node == NULL)
    {
        return NULL;
    }

    // 先寻找左子树
    DATADOU** result = TreeFindPostOrder(&((*node)->TRnode.Lchil), index);
    if (result != NULL)
    {
        return result;
    }

    // 再寻找右子树
    result = TreeFindPostOrder(&((*node)->TRnode.Rchil), index);
    if (result != NULL)
    {
        return result;
    }

    

    // 目标节点已找到
    if (*index == 0)
    {
        return node;
    }

    // 最后访问当前节点，倒计数
    (*index)--;

    return NULL;
}


// 根据完全二叉树的层序编号寻找节点
// head 从 1 开始，1 表示根节点
// 找到返回节点指针，找不到返回 NULL
static DATADOU** TreeFindByLevel(HEAD* head,size_t index)
{
    if (head->root == NULL || index == 0)
    {
        return NULL;
    }

    // 根节点编号为 1，不需要移动
    if (index == 1)
    {
        return (DATADOU**)&(head->root);
    }

    // 保存从目标节点到根节点的方向
    size_t path[sizeof(size_t) * 8];
    size_t depth = 0;

    while (index > 1)
    {
        path[depth++] = index % 2;
        index /= 2;
    }

    // 从根节点出发，反向使用路径
    DATADOU** node = (DATADOU**)&(head->root);

    while (depth > 0)
    {
        size_t direction = path[--depth];

        if (direction == 0)
        {
            node = &((*node)->TRnode.Lchil);
        }
        else
        {
            node = &((*node)->TRnode.Rchil);
        }

        if (node == NULL)
        {
            return NULL;
        }
    }

    return node;
}

DATADOU** TreeFindByOrder(HEAD* head,size_t index,TREE_ORDER order)
{
    if (head->type != TREE)
    {
        return NULL;
    }
    
    DATADOU* node = head->root;
    DATADOU** trnd = NULL;
    size_t num = index;
    switch (order)
    {
    case TREE_PREORDER:
        trnd = TreeFindPreOrder(&node,&num);
        break;

    case TREE_INORDER:
        trnd = TreeFindInOrder(&node,&num);
        break;

    case TREE_POSTORDER:
        trnd = TreeFindPostOrder(&node,&num);
        break;

    case TREE_LEVELORDER:
        
        trnd = TreeFindByLevel(head,num);
        break;

    default:
        break;
    }
    if (trnd == NULL)
    {
        return NULL;
    }
    
    return trnd;
}

void RTreeAdd(HEAD *HEAD,DATADOU *NODE)
{
    if (HEAD->type != TREE || NODE->TRnode.Rchil != NULL)
    {
        return;
    }
    DATADOU *TRNODE=malloc(sizeof(*TRNODE));
    TRNODE->deepth=NODE->deepth+1;
    NODE->TRnode.Rchil=TRNODE;
    TRNODE->TRnode.Lchil=NULL;
    TRNODE->TRnode.Rchil=NULL;
    
}

void LTreeAdd(HEAD *HEAD,DATADOU *NODE)
{
    if (HEAD->type != TREE || NODE->TRnode.Lchil != NULL)
    {
        return;
    }
    DATADOU *TRNODE=malloc(sizeof(*TRNODE));
    TRNODE->deepth=NODE->deepth+1;
    NODE->TRnode.Lchil=TRNODE;
    TRNODE->TRnode.Lchil=NULL;
    TRNODE->TRnode.Rchil=NULL;   
}


void ALLTreeDel(DATADOU *NODE)      //删除该节点以下所有节点
{
    if (NODE == NULL)
    {
        return;
    }
    
    ALLTreeDel(NODE->TRnode.Lchil);
    ALLTreeDel(NODE->TRnode.Rchil);
    free(NODE);
    
    
}

HEAD *InitGraph()
{

    HEAD *HEAD=malloc(sizeof(*HEAD));
    HEAD->type=GRAPH;
    HEAD->size=4;
    int *adjmatrix=calloc(HEAD->size*HEAD->size,sizeof(int));
    HEAD->root=adjmatrix;
    HEAD->feature.Graph.nodenum=0;
    return HEAD;
}

void GraphResize(HEAD *HEAD,int newcapacity)
{
    if (HEAD->type!=GRAPH||newcapacity<HEAD->feature.Graph.nodenum)
    {
        return;
    }
    int *NEW_adjmatrix=calloc(newcapacity*newcapacity,sizeof(int));
    int *new_aim=NEW_adjmatrix;
    int *old_aim=HEAD->root;
    for (int i = 0; i < HEAD->feature.Graph.nodenum; i++)
    {
        memcpy(new_aim,old_aim,HEAD->feature.Graph.nodenum*sizeof(int));
        old_aim=old_aim+HEAD->size;
        new_aim=new_aim+newcapacity;
    }
    free(HEAD->root);
    HEAD->root=NEW_adjmatrix;
    HEAD->size=newcapacity;
    
}

void GraphEDGECharge(HEAD *HEAD,int x,int y,int power)
{
    if (HEAD->type!=GRAPH||x>=HEAD->feature.Graph.nodenum||y>=HEAD->feature.Graph.nodenum)
    {
        return;
    }
    int aim=HEAD->size*y+x;
    int *adjmatrix=HEAD->root;
    adjmatrix[aim]=power;
    
}



HEAD *GS_containercreate(TYPE type)
{

    switch (type)
    {
    case VECTOR:
        return InitEncharge();
        break;
    
    case LIST:
        return InitList();
        break;

    case DOULIST:
        return InitDouList();
        break;

    case TREE:
        return InitTree();
        break;

    case GRAPH:
        return InitGraph();
        break;
    
    default:
        break;
    }
    return NULL;
}

