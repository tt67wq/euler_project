/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

struct node {
        int val;
        int lv;
};

void dfs(struct TreeNode *node, int lv, struct node **parents) {
        if (node == NULL) {
                return;
        }
        if (node->left != NULL) {
                struct node *tmp = (struct node *)malloc(sizeof(struct node));
                tmp->lv = lv;
                tmp->val = node->val;
                parents[node->left->val] = tmp;
                dfs(node->left, lv + 1, parents);
        }

        if (node->right != NULL) {
                struct node *tmp = (struct node *)malloc(sizeof(struct node));
                tmp->lv = lv;
                tmp->val = node->val;
                parents[node->right->val] = tmp;
                dfs(node->right, lv + 1, parents);
        }
}

bool isCousins(struct TreeNode *root, int x, int y) {
        struct node **parents = (struct node **)calloc(100, sizeof(struct node *));
        dfs(root, 0, parents);

        if (parents[x] != NULL && parents[y] != NULL && parents[x]->lv == parents[y]->lv &&
            parents[x]->val != parents[y]->val) {
                return true;
        }
        return false;
}

int main() { return 0; }