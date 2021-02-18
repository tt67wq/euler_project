/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-18
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

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

bool validBST(struct TreeNode *root, int *maxVal, int *minVal) {
        if (root == NULL) {
                return true;
        }

        if (root->left == NULL && root->right == NULL) {
                (*minVal) = root->val;
                (*maxVal) = root->val;
                return true;
        }

        int leftMax, leftMin, rightMin, rightMax;
        leftMax = INT32_MIN;
        leftMin = INT32_MAX;
        rightMax = INT32_MIN;
        rightMin = INT32_MAX;

        if (root->left != NULL) {
                if (!validBST(root->left, &leftMax, &leftMin)) {
                        return false;
                } else {
                        (*minVal) = leftMin;
                        if (root->val <= leftMax) {
                                return false;
                        }
                }
        } else {
                (*minVal) = root->val;
        }
        if (root->right != NULL) {
                if (!validBST(root->right, &rightMax, &rightMin)) {
                        return false;
                } else {
                        (*maxVal) = rightMax;
                        if (root->val >= rightMin) {
                                return false;
                        }
                }
        } else {
                (*maxVal) = root->val;
        }

        return true;
}

bool isValidBST(struct TreeNode *root) {
        int max, min;
        return validBST(root, &max, &min);
}

int main() {
        struct TreeNode root;
        root.val = 2147483647;
        root.left = NULL;
        root.right = NULL;

        printf("%d\n", isValidBST(&root));
        return 0;
}