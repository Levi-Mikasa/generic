#include <generic_dstree.h>

size_t TreeDataDestroyAll(DATADOU *node, GS_datadestroy destroy)
{

}


int TreeCompleteInsert(HEAD* head, void* dat)
{
    if (head->type != TREE)
    {
        return 1;
    }
    DATADOU **node = (DATADOU**)&head->root;
    
    if (head->size == 0)
    {
        (*node)->dat = dat;
        (*node)->deepth = 0;
        head->size = 1;
        return 0;
    }
    size_t next_index = head->size + 1;
    size_t parent_index = next_index / 2;

    node = TreeFindByOrder(head,parent_index,TREE_LEVELORDER);

    // 必须先检查查出来的节点是否存在！
    if (node == NULL || *node == NULL)
    {
        // 处理错误：比如父节点根本不存在
        return 1; 
    }

    if (next_index % 2 == 1)
    {
        RTreeAdd(head,*node);
        head->size = next_index;
        (*node)->TRnode.Rchil->dat = dat;

    }else{
        LTreeAdd(head,*node);
        head->size = next_index;
        (*node)->TRnode.Lchil->dat = dat;
    }

    return 0;
    
    
    
}


void* TreeDataRead(HEAD* head,size_t index,TREE_ORDER order)
{
    if (head->type != TREE)
    {
        return NULL;
    }
    
    DATADOU** node = TreeFindByOrder(head,index,order);
    if (node == NULL)
    {
        return NULL;
    }
    
    return (*node)->dat;
}


int TreeDataWrite(HEAD* head,size_t index,TREE_ORDER order,void* dat)
{
    if (head->type != TREE)
    {
        return 1;
    }
    
    DATADOU** node = TreeFindByOrder(head,index,order);
    if (node == NULL)
    {
        return 1;
    }
    
    (*node)->dat = dat;
    return 0;
}


void TreeDataDelAPIbyPath(HEAD *head,char *Aim,GS_datadestroy destroy)
{
    if (head == NULL || head->type != TREE ||
        Aim == NULL || destroy == NULL)
    {
        return;
    }

    DATADOU **node = (DATADOU**)&head->root;
    node = TREEFindbyPath(Aim, node);

    if (node == NULL || *node == NULL)
    {
        return;
    }

    // 先释放目标子树中的数据
    // TreeDataDestroyAll 需要遍历子树，并对每个节点的 dat
    // 调用 destroy；它不是现有接口，需按你的节点结构实现。
    

    // 再释放目标子树的节点空间
    size_t count = TreeDataDestroyAll(*node, destroy);
    ALLTreeDel(*node);
    *node = NULL;

    head->size -= count;
}

void TreeDataDelAPIbyOrder(HEAD *head,TREE_ORDER order,size_t index,GS_datadestroy destroy)
{
    if (head == NULL || head->type != TREE ||
        destroy == NULL)
    {
        return;
    }

    DATADOU **node = NULL;

    node = TreeFindByOrder(head,index,order);

    if (node == NULL || *node == NULL)
    {
        return;
    }

    // 先释放数据，再释放节点
    

    size_t count = TreeDataDestroyAll(*node, destroy);
    ALLTreeDel(*node);
    *node = NULL;

    head->size -= count;
}