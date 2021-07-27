/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-07-27
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。
// 如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一个。

// 更正式地说，root.val = min(root.left.val, root.right.val) 总成立。

// 给出这样的一个二叉树，你需要输出所有节点中的第二小的值。如果第二小的值不存在的话，输出 -1 。

// 树中节点数目在范围 [1, 25] 内
// 1 <= Node.val <= 231 - 1
// 对于树中每个节点 root.val == min(root.left.val, root.right.val)

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/second-minimum-node-in-a-binary-tree
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void dfs(struct TreeNode *node, int rootVal, int *min) {
        if (node == NULL) {
                return;
        }

        if (node->val > rootVal && (*min == -1 || node->val < *min)) {
                *min = node->val;
        }
        dfs(node->left, rootVal, min);
        dfs(node->right, rootVal, min);
}

int findSecondMinimumValue(struct TreeNode *root) {
        if (root->left == NULL) {
                return -1;
        }

        int ans = -1;
        dfs(root, root->val, &ans);
        return ans;
}

int main() { return 0; }