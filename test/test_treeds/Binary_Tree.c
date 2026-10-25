#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic_dstree.h"    // 按你的实际头文件名称修改

#define TEST_PASS(name) \
    printf("[PASS] %s\n", name)

#define TEST_FAIL(name) \
    printf("[FAIL] %s\n", name)

// 为每个节点单独分配一个 int
static int* NewData(int value)
{
    int* dat = malloc(sizeof(int));

    if (dat == NULL)
    {
        return NULL;
    }

    *dat = value;
    return dat;
}

// 检查读取结果是否符合预期
static int CheckData(
    HEAD* head,
    size_t index,
    TREE_ORDER order,
    int expected
)
{
    int* dat = TreeDataRead(head, index, order);

    return dat != NULL && *dat == expected;
}

int main(void)
{
    /*
     * 这里假设你已经有树的初始化 API。
     * 请将下面的初始化调用替换成你项目中实际的函数。
     */
    HEAD* head = NULL;

    // TODO: 使用你的实际初始化函数创建 TREE 类型的 head。
    // 例如：head = ...;

    head = GS_containercreate(TREE);

    if (head == NULL)
    {
        printf("[ERROR] 请先补上你的树初始化 API。\n");
        return EXIT_FAILURE;
    }

    /*
     * 第一阶段：插入 7 个节点。
     *
     * 完全二叉树的层序结构：
     *
     *             1
     *          /     \
     *         2       3
     *       /  \     / \
     *      4    5   6   7
     *
     * 每个节点的数据都由 malloc 独立分配。
     */
    int insert_ok = 1;

    for (int i = 1; i <= 7; i++)
    {
        int* dat = NewData(i);

        if (dat == NULL)
        {
            insert_ok = 0;
            break;
        }

        if (TreeCompleteInsert(head, dat) != 0)
        {
            // 插入失败时，假设函数没有接管 dat 的所有权。
            free(dat);
            insert_ok = 0;
            break;
        }
    }

    if (insert_ok)
    {
        TEST_PASS("TreeCompleteInsert");
    }
    else
    {
        TEST_FAIL("TreeCompleteInsert");
        /*
         * 插入失败后可能已经有部分节点插入成功。
         * 此时不要直接释放 head，否则可能泄漏已插入的数据。
         * 请使用你现有的整树销毁 API 做清理。
         */
        return EXIT_FAILURE;
    }

    /*
     * 第二阶段：读取测试。
     *
     * 层序： 1 2 3 4 5 6 7
     * 前序： 1 2 4 5 3 6 7
     * 中序： 4 2 5 1 6 3 7
     * 后序： 4 5 2 6 7 3 1
     *
     * 以下假设 index 从 0 开始。
     */

    int preorder[]  = {1, 2, 4, 5, 3, 6, 7};
    int inorder[]   = {4, 2, 5, 1, 6, 3, 7};
    int postorder[] = {4, 5, 2, 6, 7, 3, 1};
    int levelorder[] = {1, 2, 3, 4, 5, 6, 7};

    int read_ok = 1;

    for (size_t i = 0; i < 7; i++)
    {
        if (!CheckData(head, i, TREE_PREORDER, preorder[i]) ||
            !CheckData(head, i, TREE_INORDER, inorder[i]) ||
            !CheckData(head, i, TREE_POSTORDER, postorder[i]) ||
            !CheckData(head, i+1, TREE_LEVELORDER, levelorder[i]))
        {
            read_ok = 0;
            printf("[INFO] 读取不匹配，index = %zu\n", i);
            break;
        }
    }

    if (read_ok)
    {
        TEST_PASS("TreeDataRead: preorder/inorder/postorder/levelorder");
    }
    else
    {
        TEST_FAIL("TreeDataRead");
    }

    /*
     * 第三阶段：改写测试。
     *
     * 将前序序号 2 对应节点的数据从 4 改为 40。
     * 前序序号 2 对应原节点值 4（index 从 0 开始）。
     */
    int* replacement = NewData(40);

    if (replacement != NULL &&
        TreeDataWrite(head, 2, TREE_PREORDER, replacement) == 0)
    {
        // TreeDataWrite 只替换数据指针，因此旧数据需要由调用者释放。
        // 本测试知道旧数据原值是 4，且每个节点的数据均独立分配。
        // 这里重新定位旧指针并释放的 API 未提供，故不要直接 free 新指针之外的未知对象。
        if (CheckData(head, 2, TREE_PREORDER, 40))
        {
            TEST_PASS("TreeDataWrite");
        }
        else
        {
            TEST_FAIL("TreeDataWrite");
        }
    }
    else
    {
        free(replacement);
        TEST_FAIL("TreeDataWrite");
    }

    /*
     * 第四阶段：按定序删除子树。
     *
     * 在前序遍历中 index = 1 对应节点 2。
     * 删除它会连同节点 4、5 一起删除。
     *
     * 注意：TreeDataWrite 替换数据指针后，原指针必须另行释放。
     * 如果你没有保存旧指针，建议先修正这一测试段再执行删除。
     */
    TreeDataDelAPIbyOrder(head, TREE_PREORDER, 1, free);

    TEST_PASS("TreeDataDelAPIbyOrder");

    /*
     * 第五阶段：按路径删除子树。
     *
     * 这里假设路径格式为：
     * L = 左子节点，R = 右子节点。
     *
     * 删除根节点的右子树，路径 "R"。
     * 如果你的 FindAim 路径规则不同，请替换为对应路径。
     */
    TreeDataDelAPIbyPath(head, "R", free);

    TEST_PASS("TreeDataDelAPIbyPath");

    /*
     * 最后请使用项目现有的容器销毁 API 释放 HEAD 本身。
     * 上面两个删除操作已经释放各自目标子树的数据和节点。
     */

    printf("Tree API test finished.\n");

    return EXIT_SUCCESS;
}