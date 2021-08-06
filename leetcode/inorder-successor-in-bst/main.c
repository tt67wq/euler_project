/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-08-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回
// null 。

// 节点 p 的后继是值比 p.val 大的节点中键值最小的节点，即按中序遍历的顺序节点 p 的下一个节点。

//  

// 示例 1：

// 输入：root = [2,1,3], p = 1
// 输出：2
// 解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
// 示例 2：

// 输入：root = [5,3,6,2,4,null,null,1], p = 6
// 输出：null
// 解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
//  

// 提示：

// 树中节点的数目在范围 [1, 104] 内。
// -105 <= Node.val <= 105
// 树中各节点的值均保证唯一。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/P5rCT8
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void dfs(struct TreeNode *root, struct TreeNode *p, struct TreeNode **res) {
        if (root == NULL) {
                return;
        }

        if (*res != NULL) {
                return;
        }

        dfs(root->left, p, res);
        if (root->val > p->val && *res == NULL) {
                *res = root;
        }
        dfs(root->right, p, res);
        return;
}

struct TreeNode *inorderSuccessor(struct TreeNode *root, struct TreeNode *p) {
        struct TreeNode *res;
        res = NULL;
        dfs(root, p, &res);
        return res;
}

int main() { return 0; }