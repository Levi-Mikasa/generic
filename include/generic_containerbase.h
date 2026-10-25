# ifndef TOOL_H
# define TOOL_H
# include <stdlib.h>

typedef void (*GS_datadestroy)(void *dat);   //销毁函数

typedef struct data
{
    void* dat;
    struct data *NEXT;
}DATA;

typedef struct tree     //二叉树节点兼双向链表节点
{
    void* dat;
    union 
    {
    struct treenode {struct tree *Lchil,*Rchil}TRnode;  // 二叉树节点
    struct listnode {struct tree *PrNode,*AfNode}LInode;// 双向链表节点
    };
    

    int deepth;
}DATADOU;

typedef enum{
    VECTOR,
    LIST,
    DOULIST,
    TREE,
    GRAPH
}TYPE;

typedef enum TreeOrder  //二叉树表达顺序
{
    TREE_PREORDER,   // 前序：根、左、右
    TREE_INORDER,    // 中序：左、根、右
    TREE_POSTORDER,   // 后序：左、右、根
    TREE_LEVELORDER
} TREE_ORDER;


typedef struct head
{
    TYPE type;      // 标识当前是什么结构
    size_t size;       // 当前结构空间大小
    union TYPE
    {
        struct array
        {
            //当前数据量
            size_t num;
            void* vectorpointersignal;   //数据标记
        }Array;
        struct lists
        {
            union LISTTYPE
            {
                DATA *LastNode;       //普通链表节点
                DATADOU *DouLastNode; //双向链表末端节点
            }ListType;
        }Lists;
        struct trees
        {
            // 树深度
            size_t deepth;
        }Trees;
        struct graph                 //邻接矩阵
        {
            size_t nodenum;
        }Graph;
        
        
    }feature;
    
    void *root;      // 指向数据结构的起点
}HEAD;

//头插，尾插
typedef enum{
    HEAD_ADD,
    TAIL_ADD
}ADD_LOCAL;


//可变数组
HEAD *InitEncharge();
void EnchargeSpaceset(HEAD* head,size_t capacity);
//链表
HEAD *InitList();
void ListAdd(HEAD *HEAD,ADD_LOCAL local);
void ListDel(HEAD *HEAD,int num);
DATA *listsearch(HEAD *head,size_t local);
//双向链表
HEAD *InitDouList();
void DoublyListAdd(HEAD *HEAD);
void DoublyListDel(HEAD *HEAD,int num);
//树
HEAD *InitTree();
void RTreeAdd(HEAD *HEAD,DATADOU *NODE);
void LTreeAdd(HEAD *HEAD,DATADOU *NODE);
DATADOU** TreeFindByOrder(HEAD* head,size_t index,TREE_ORDER order);
DATADOU** TREEFindbyPath(char *Aim,DATADOU **NODE);
void ALLTreeDel(DATADOU *NODE);
// 图（邻接矩阵）
HEAD *InitGraph();
void GraphResize(HEAD *HEAD,int newcapacity);
void GraphEDGECharge(HEAD *HEAD,int x,int y,int power);



// 容器创建
HEAD *GS_containercreate(TYPE type);





# endif