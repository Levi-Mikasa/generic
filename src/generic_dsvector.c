#include "generic_dsvector.h"
#include <string.h>

size_t GS_vectorsize(HEAD *head)
{
    return head->size;
}

void GS_vectorstackpush(HEAD* head,void* data)
{
    if (head->type != VECTOR)
    {
        return;
    }
    //容器容量少于实际数据量，重新设置容器空间
    if (head->size <= head->feature.Array.num)
    {
        EnchargeSpaceset(head,head->feature.Array.num+1);
    }
    


    DATA* Array = (DATA*)(head->root);
    Array[head->feature.Array.num].dat = data;
    head->feature.Array.num++;

    
}

void* GS_vectorstackpop(HEAD* head)
{
    if (head->type != VECTOR || head->feature.Array.num == 0 || head->size == 0)
    {
        return NULL;
    }

    DATA* Array = head->root;
    DATA* data = malloc(sizeof(DATA));
    data->dat = Array[head->feature.Array.num-1].dat;
    head->feature.Array.num--;
    return data->dat;
    
}

void *GS_vectorstackpeek(HEAD *head)
{
    DATA* dat = head->root;
    void* result = dat[head->feature.Array.num-1].dat;
    return result;
}

void *GS_vectorstackback(HEAD *head)
{
    DATA* dat = head->root;
    void* result = dat[0].dat;
    return result;
}

typedef struct queuepointer
{
    size_t front; //队列前端指针
    size_t raer; //队列后端指针
} VECTORPOINTER;


int GS_vectorqueueexpand(HEAD* head, size_t amount)
{
    if (head == NULL || head->type != VECTOR || amount == 0)
    {
        return 0;
    }

    size_t oldsize = head->size;
    size_t num = head->feature.Array.num;

    if (amount > SIZE_MAX - oldsize)
    {
        return 0;
    }

    size_t newsize = oldsize + amount;

    if (newsize > SIZE_MAX / sizeof(DATA))
    {
        return 0;
    }

    VECTORPOINTER* signal =
        head->feature.Array.vectorpointersignal;

    if (num > 0 && signal == NULL)
    {
        return 0;
    }

    size_t oldfront = num > 0 ? signal->front : 0;
    size_t oldraer  = num > 0 ? signal->raer : 0;

    // 扩容前记录旧数组地址
    DATA* oldArray = head->root;

    // 第一层统一调整容量
    EnchargeSpaceset(head, newsize);

    DATA* newArray = head->root;

    if (newArray == NULL)
    {
        return 0;
    }

    // 已绕回：把末尾那段数据向后搬运
    if (num > 0 && oldfront > oldraer)
    {
        size_t move_num = oldsize - oldfront;

        memmove(
            newArray + oldfront + amount,
            newArray + oldfront,
            move_num * sizeof(DATA)
        );

        signal->front = oldfront + amount;
    }

    return 1;
}

int GS_vectorqueueshrink(HEAD* head)      // 缩容函数
{
    if (head == NULL || head->type != VECTOR)
    {
        return 0;
    }

    size_t oldsize = head->size;
    size_t num = head->feature.Array.num;

    // 容量太小，没有必要继续缩容
    if (oldsize <= 4)
    {
        return 0;
    }

    // 元素数量超过容量的一半，不缩容
    if (num > oldsize / 2)
    {
        return 0;
    }

    // 计算原容量的四分之三，避免乘法溢出
    size_t newsize = (oldsize / 4) * 3 + ((oldsize % 4) * 3) / 4;

    if (newsize == 0)
    {
        newsize = 1;
    }

    // 新容量不能小于当前元素数量
    if (newsize < num)
    {
        return 0;
    }

    if (newsize > SIZE_MAX / sizeof(DATA))
    {
        return 0;
    }

    DATA* Array = head->root;

    VECTORPOINTER* signal = head->feature.Array.vectorpointersignal;

    if (num > 0 && signal == NULL)
    {
        return 0;
    }

    DATA* newArray = malloc(newsize * sizeof(DATA));

    if (newArray == NULL)
    {
        return 0;
    }

    if (num > 0)
    {
        size_t front = signal->front;
        size_t raer = signal->raer;

        if (front > raer)
        {
            // 已绕回：先复制数组末尾的部分
            size_t first_num = oldsize - front;

            memcpy(
                newArray,
                Array + front,
                first_num * sizeof(DATA)
            );

            // 再复制绕回数组开头的部分
            size_t second_num = num - first_num;

            memcpy(
                newArray + first_num,
                Array,
                second_num * sizeof(DATA)
            );
        }
        else
        {
            // 未绕回：所有元素位于一个连续区间
            memcpy(
                newArray,
                Array + front,
                num * sizeof(DATA)
            );
        }
    }

    // 数据复制完成后，才释放原数组
    free(Array);

    head->root = newArray;
    head->size = newsize;

    // 缩容后队列从数组开头连续排列
    signal->front = 0;
    signal->raer = (num == 0) ? 0 : num - 1;

    return 1;
}

void* GS_vectorqueuepush(HEAD* head,void* dat)
{
    if (head->type != VECTOR)
    {
        return NULL;
    }
    
    if (!head->feature.Array.vectorpointersignal) //队列指针组未初始化
    {
        VECTORPOINTER* vectorsignal = malloc(sizeof(VECTORPOINTER));
        vectorsignal->front = 0;
        vectorsignal->raer = 0;
        head->feature.Array.vectorpointersignal = vectorsignal;
    }
    
    if (head->size == head->feature.Array.num)       //当容量被占满
    {
        /* 扩容:扩容应该定量扩容 */
        int error = GS_vectorqueueexpand(head,10);
        if (error)
        {
            /* 扩容失败 */
        }
        
    }   
    
    VECTORPOINTER* vectorsignal = head->feature.Array.vectorpointersignal;
    DATA* Array = head->root;

    if (head->feature.Array.num == 0 || vectorsignal->raer == head->size-1)          //第一次入队 || 插入到空间物理边界以外（绕回）
    {
        Array[0].dat = dat;
        vectorsignal->raer = 0;
        head->feature.Array.num++;
        return vectorsignal;
    }
    
    Array[vectorsignal->raer+1].dat = dat;
    vectorsignal->raer++;
    head->feature.Array.num++;
    return vectorsignal;
}

void* GS_vectorqueuepop(HEAD* head)
{
    if (head->type != VECTOR || head->feature.Array.num == 0)
    {
        return NULL;
    }

    

    DATA* Array = head->root;
    VECTORPOINTER* vectorsignal = head->feature.Array.vectorpointersignal;
    if (vectorsignal->front == head->size-1)
    {
        /* 绕回 */
        vectorsignal->front = 0;
    }
    
    // DATA* ans = malloc(sizeof(DATA));

    // if (ans == NULL)
    // {
    //     return NULL; // 内存分配失败
    // }
    // ans->dat = Array[vectorsignal->front].dat;

    //DATA* ans = &Array[vectorsignal->front];

    void* result = Array[vectorsignal->front].dat;

    head->feature.Array.num--;
    vectorsignal->front++;
    if (head->size >= head->feature.Array.num*2)     //缩容：当总容量大于被使用容量的两倍
    {
        /* 缩容 */
        int error = GS_vectorqueueshrink(head);
        if (!error)
        {
            /* 缩容失败 */
        }
        
    }
    if (head->feature.Array.num == 0)
    {
        head->root = NULL;
    }
    
    
    return result;
    
}

int GS_vectorempty(HEAD* head)
{
    int i = 0;
    if (head->feature.Array.num == 0)
    {
        i = 1;
    }
    return i;
    
}

int GS_vectorcontainerempty(HEAD *head)
{
    return head == NULL || head->root == NULL;
}


void GS_vectordestroy(HEAD **head,GS_datadestroy des)
{
    if(head == NULL||*head ==NULL)
    {
        return;
    }

    DATA *node = (*head)->root;

    while((*head)->size != 0)
    {
        
        des(node[(*head)->size-1].dat);
        

        (*head)->size--;
    }
    free(node);
    free(*head);
    *head=NULL;
}

void* GS_vectorqueuepeek(HEAD* head)
{
    VECTORPOINTER *vectorsignal = head->feature.Array.vectorpointersignal;
    DATA* dat = head->root;
    return dat[vectorsignal->raer].dat;
}

void* GS_vectorqueueback(HEAD* head)
{
    VECTORPOINTER *vectorsignal = head->feature.Array.vectorpointersignal;
    DATA* dat = head->root;
    return dat[vectorsignal->front].dat;
}







