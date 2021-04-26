/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-26
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

// 给你一棵二叉搜索树，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，
// 使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。

//  

// 示例 1：

// 输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
// 输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
// 示例 2：

// 输入：root = [5,1,7]
// 输出：[1,null,5,null,7]
//  

// 提示：

// 树中节点数的取值范围是 [1, 100]
// 0 <= Node.val <= 1000

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/increasing-order-search-tree
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

struct lnode {
        int val;
        STAILQ_ENTRY(lnode) next;
};

STAILQ_HEAD(lhead, lnode);

static void inorder(const struct TreeNode *root, struct lhead *head) {
        if (root == NULL) {
                return;
        }
        inorder(root->left, head);
        struct lnode *m = (struct lnode *)malloc(sizeof(struct lnode));
        m->val = root->val;
        STAILQ_INSERT_TAIL(head, m, next);
        inorder(root->right, head);
}

struct TreeNode *increasingBST(struct TreeNode *root) {
        struct lhead *head = (struct lhead *)malloc(sizeof(struct lhead));
        STAILQ_INIT(head);
        inorder(root, head);

        struct TreeNode *ans = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        struct TreeNode *ansp = ans;
        struct lnode *tmp;

        STAILQ_FOREACH(tmp, head, next) {
                struct TreeNode *m = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                m->val = tmp->val;
                m->left = NULL;
                m->right = NULL;
                ansp->right = m;
                ansp = ansp->right;
        }
        return ans->right;
}

int main() {
        struct TreeNode n0, n1, n2, n3, n4, n5, n6, n7, n8;
        n0.val = 1;
        n1.val = 2;
        n2.val = 3;
        n3.val = 4;
        n4.val = 5;
        n5.val = 6;
        n6.val = 7;
        n7.val = 8;
        n8.val = 9;

        n4.left = &n2;
        n4.right = &n5;
        n2.left = &n1;
        n2.right = &n3;
        n3.left = NULL;
        n3.right = NULL;
        n1.left = &n0;
        n1.right = NULL;
        n0.left = NULL;
        n0.right = NULL;
        n5.left = NULL;
        n5.right = &n7;
        n7.left = &n6;
        n7.right = &n8;
        n6.left = NULL;
        n6.right = NULL;
        n8.left = NULL;
        n8.right = NULL;

        struct TreeNode *ans = increasingBST(&n4);

        while (ans != NULL) {
                printf("%d ", ans->val);
                ans = ans->right;
        }
        puts("");

        return 0;
}