/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-02
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

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

#define MAX 1000

/*       5 */
/*      / \ */
/*     4   8 */
/*    /   / \ */
/*   11  13  4 */
/*  /  \    / \ */
/* 7    2  5   1 */

void dfs(struct TreeNode *root, int acc, int *nums, int idx, int *size, int **res, int **colSize) {
        if (root->left == NULL && root->right == NULL) {
                if (acc == root->val) {
                        int *tmp = (int *)calloc(idx + 1, sizeof(int));
                        for (int i = 0; i < idx; i++) {
                                tmp[i] = nums[i];
                        }
                        tmp[idx] = root->val;
                        res[(*size)] = tmp;
                        (*colSize)[(*size)] = idx + 1;
                        (*size)++;
                }
                return;
        }

        acc -= root->val;
        nums[idx] = root->val;
        if (root->left != NULL)
                dfs(root->left, acc, nums, idx + 1, size, res, colSize);
        if (root->right != NULL)
                dfs(root->right, acc, nums, idx + 1, size, res, colSize);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **pathSum(struct TreeNode *root, int sum, int *returnSize, int **returnColumnSizes) {
        if (root == NULL) {
                (*returnSize) = 0;
                (*returnColumnSizes) = NULL;
                return NULL;
        }
        int **res = (int **)malloc(sizeof(int *) * MAX);
        (*returnColumnSizes) = (int *)malloc(sizeof(int) * MAX);
        (*returnSize) = 0;
        int nums[MAX] = {0};

        dfs(root, sum, nums, 0, returnSize, res, returnColumnSizes);

        return res;
}

struct TreeNode *new_node(int val) {
        struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        return node;
}

int main() {
        struct TreeNode *n0 = new_node(1);
        struct TreeNode *n1 = new_node(2);

        n0->left = n1;

        int *colSize;
        int size = 0;

        int **res = pathSum(n0, 1, &size, &colSize);

        for (int i = 0; i < size; i++) {
                for (int j = 0; j < colSize[i]; j++) {
                        printf("%d ", res[i][j]);
                }
                printf("\n");
        }

        return 0;
}
