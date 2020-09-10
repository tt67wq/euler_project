/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-10
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

void countDepth(struct TreeNode *root, int *depth) {
        *depth = -1;
        while (root) {
                root = root->left;
                (*depth)++;
        }
}

bool exist(int index, int depth, struct TreeNode *node) {
        int left = 0, right = (1 << depth) - 1;
        for (int i = 0; i < depth; i++) {
                int pivot = left + (right - left) / 2;
                if (index <= pivot) {
                        node = node->left;
                        right = pivot;
                } else {
                        node = node->right;
                        left = pivot + 1;
                }
        }
        return node != NULL;
}

int countNodes(struct TreeNode *root) {

        if (!root) {
                return 0;
        }

        int depth = 0;
        countDepth(root, &depth);

        if (depth == 0) {
                return 1;
        }

        int left = 0, right = (1 << depth) - 1;
        while (left <= right) {
                int pivot = left + (right - left) / 2;
                if (exist(pivot, depth, root)) {
                        left = pivot + 1;
                } else {
                        right = pivot - 1;
                }
        }
        return (1 << depth) - 1 + left;
}

int main() {
        struct TreeNode a0 = {1, NULL, NULL};
        struct TreeNode a1 = {2, NULL, NULL};
        struct TreeNode a2 = {3, NULL, NULL};
        struct TreeNode a3 = {4, NULL, NULL};
        struct TreeNode a4 = {5, NULL, NULL};
        struct TreeNode a5 = {6, NULL, NULL};

        a0.left = &a1;
        a0.right = &a2;
        a1.left = &a3;
        a1.right = &a4;
        a2.left = &a5;

        int ans = countNodes(&a0);
        printf("%d\n", ans);
        return 0;
}