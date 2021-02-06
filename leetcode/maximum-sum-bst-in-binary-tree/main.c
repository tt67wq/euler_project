/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Definition for a binary tree node.
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

int sumNodeValue(int *res, struct TreeNode *node) {
        if (node == NULL) {
                return 0;
        }
        int sum;

        sum = node->val + sumNodeValue(res, node->left) + sumNodeValue(res, node->right);
        *res = MAX(*res, sum);
        return sum;
}

bool isBST(struct TreeNode *root, int min, int max) {
        if (root == NULL) {
                return true;
        }

        return (min < root->val && root->val < max) && (isBST(root->left, min, root->val)) &&
               (isBST(root->right, root->val, max));
}

void maxSumBSTTMP(int *res, struct TreeNode *node) {
        if (isBST(node, INT32_MIN, INT32_MAX)) {
                sumNodeValue(res, node);
                return;
        }
        maxSumBSTTMP(res, node->left);
        maxSumBSTTMP(res, node->right);
}

int maxSumBST(struct TreeNode *root) {
        int res = 0;
        maxSumBSTTMP(&res, root);
        return res;
}

int main() { return 0; }