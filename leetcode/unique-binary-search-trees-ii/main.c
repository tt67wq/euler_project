/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-11
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define MAX 10000

/* Definition for a binary tree node. */
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};
typedef struct TreeNode Node;

// build bin search tree using [lo, hi)
Node **_generateTrees(int lo, int hi, int *returnSize) {
        if (lo == hi) {
                (*returnSize) = 1;
                Node **res = (Node **)calloc((*returnSize), sizeof(Node *));
                res[0] = NULL;
                return res;
        }

        if (lo + 1 == hi) {
                // only one num
                Node *root = (Node *)calloc(1, sizeof(Node));
                root->val = lo;
                root->left = NULL;
                root->right = NULL;
                (*returnSize) = 1;
                Node **res = (Node **)calloc((*returnSize), sizeof(Node *));
                res[0] = root;
                return res;
        }

        // choose a root
        (*returnSize) = 0;
        Node **res = (Node **)calloc(MAX, sizeof(Node *));
        for (int r = lo; r < hi; r++) {

                int leftSize, rightSize;
                Node **leftNodes = _generateTrees(lo, r, &leftSize);
                Node **rightNodes = _generateTrees(r + 1, hi, &rightSize);

                for (int i = 0; i < leftSize; i++) {
                        for (int j = 0; j < rightSize; j++) {
                                Node *root = (Node *)calloc(1, sizeof(Node));
                                root->val = r;
                                root->left = leftNodes[i];
                                root->right = rightNodes[j];
                                res[(*returnSize)++] = root;
                        }
                }
                free(leftNodes);
                free(rightNodes);
        }
        return res;
}

/* /\** */
/*  * Note: The returned array must be malloced, assume caller calls free(). */
/*  *\/ */
struct TreeNode **generateTrees(int n, int *returnSize) {
        if (n == 0) {
                (*returnSize) = 0;
                return NULL;
        }
        return _generateTrees(1, n + 1, returnSize);
}

int main() { return 0; }
