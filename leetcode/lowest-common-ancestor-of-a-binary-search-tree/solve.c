/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-02-27
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q) {
        struct TreeNode *t;

        if (p->val > q->val) {
                t = p;
                p = q;
                q = t;
        }

        // now p < q

        // left
        if (q->val < root->val) {
                return lowestCommonAncestor(root->left, p, q);
        }

        // right
        if (p->val > root->val) {
                return lowestCommonAncestor(root->right, p, q);
        }

        // middle
        return root;
}

int main() { return 0; }
