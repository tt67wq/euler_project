/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给你一棵二叉树的根节点 root ，树中有 n 个节点，每个节点都有一个不同于其他节点且处于 1 到 n
// 之间的值。

// 另给你一个由 n 个值组成的行程序列 voyage ，表示 预期 的二叉树 先序遍历 结果。

// 通过交换节点的左右子树，可以 翻转 该二叉树中的任意节点。例，翻转节点 1 的效果如下：

// 请翻转 最少 的树中节点，使二叉树的 先序遍历 与预期的遍历行程 voyage 相匹配 。 

// 如果可以，则返回 翻转的 所有节点的值的列表。你可以按任何顺序返回答案。如果不能，则返回列表 [-1]。

//  

// 示例 1：

// 输入：root = [1,2], voyage = [2,1]
// 输出：[-1]
// 解释：翻转节点无法令先序遍历匹配预期行程。
// 示例 2：

// 输入：root = [1,2,3], voyage = [1,3,2]
// 输出：[1]
// 解释：交换节点 2 和 3 来翻转节点 1 ，先序遍历可以匹配预期行程。
// 示例 3：

// 输入：root = [1,2,3], voyage = [1,2,3]
// 输出：[]
// 解释：先序遍历已经匹配预期行程，所以不需要翻转节点。
//  

// 提示：

// 树中的节点数目为 n
// n == voyage.length
// 1 <= n <= 100
// 1 <= Node.val, voyage[i] <= n
// 树中的所有值 互不相同
// voyage 中的所有值 互不相同

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/flip-binary-tree-to-match-preorder-traversal
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void dfs(struct TreeNode *node, int *res, const int *voyage, const int voyageSize, int *index,
         int *returnSize) {
        if (node == NULL) {
                return;
        }
        if (node->val != voyage[(*index)++]) {
                (*returnSize) = 1;
                res[0] = -1;
                return;
        }

        if (*index < voyageSize && node->left != NULL && node->left->val != voyage[*index]) {
                res[(*returnSize)++] = node->val;
                dfs(node->right, res, voyage, voyageSize, index, returnSize);
                dfs(node->left, res, voyage, voyageSize, index, returnSize);
        } else {
                dfs(node->left, res, voyage, voyageSize, index, returnSize);
                dfs(node->right, res, voyage, voyageSize, index, returnSize);
        }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *flipMatchVoyage(struct TreeNode *root, int *voyage, int voyageSize, int *returnSize) {
        int *res = (int *)malloc(sizeof(int) * voyageSize);
        (*returnSize) = 0;
        int index = 0;

        dfs(root, res, voyage, voyageSize, &index, returnSize);
        if (res[0] == -1) {
                (*returnSize) = 1;
        }
        return res;
}

int main() {
        struct TreeNode a;
        struct TreeNode b;
        struct TreeNode c;

        a.val = 1;
        b.val = 2;
        b.left = NULL;
        b.right = NULL;
        c.val = 3;
        c.left = NULL;
        c.right = NULL;
        a.left = &b;
        a.right = &c;

        int voyage[] = {1, 3, 2};
        int returnSize;

        int *res = flipMatchVoyage(&a, voyage, 3, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", res[i]);
        }
        puts("");

        return 0;
}