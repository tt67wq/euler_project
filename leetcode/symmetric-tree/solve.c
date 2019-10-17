/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Definition for a binary tree node. */
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void exchange(struct TreeNode *node) {
        if (node != NULL) {
                struct TreeNode *tmp;

                tmp = node->left;
                node->left = node->right;
                node->right = tmp;

                exchange(node->left);
                exchange(node->right);
        }
}

bool cmpTree(struct TreeNode *node1, struct TreeNode *node2) {
        if (node1 == NULL && node2 == NULL)
                return true;

        if (node1 == NULL && node2 != NULL)
                return false;

        if (node1 != NULL && node2 == NULL)
                return false;

        if (node1->val != node2->val)
                // 按楼主的意思，这里给改个颜色
                return false;

        return cmpTree(node1->left, node2->left) &&
               cmpTree(node1->right, node2->right);
}

struct TreeNode *copyTree(struct TreeNode *node) {
        struct TreeNode *new = NULL;
        if (node == NULL)
                return NULL;
        new = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
        new->val = node->val;
        new->left = copyTree(node->left);
        new->right = copyTree(node->right);
        return new;
}

bool isSymmetric(struct TreeNode *root) {
        struct TreeNode *origin;

        origin = copyTree(root);
        exchange(root);

        return cmpTree(origin, root);
}

int main() { return 0; }
