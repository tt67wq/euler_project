/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition for a binary tree node. */
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

int *list_slice(int *list, int start, int end) {
        if (start == end)
                return NULL;
        int i, j, *sub;
        sub = (int *)calloc(end - start, sizeof(int));

        j = 0;
        for (i = start; i < end; i++)
                sub[j++] = list[i];

        return sub;
}

void print_order(int *order, int size) {
        int i;
        for (i = 0; i < size - 1; i++)
                printf("%d ", order[i]);
        printf("%d\n", order[i]);
}

struct TreeNode *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize) {

        if (inorderSize == 0 || postorderSize == 0)
                return NULL;

        /* printf("inorder -> "); */
        /* print_order(inorder, inorderSize); */
        /* printf("postorder -> "); */
        /* print_order(postorder, postorderSize); */

        struct TreeNode *tree;
        int idx;

        tree = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));

        tree->val = postorder[postorderSize - 1];

        for (idx = 0; idx < inorderSize; idx++) {
                if (inorder[idx] == tree->val)
                        break;
        }

        /* printf("idx -> %d\n", idx); */
        tree->left = buildTree(list_slice(inorder, 0, idx), idx, list_slice(postorder, 0, idx), idx);
        tree->right = buildTree(list_slice(inorder, idx + 1, inorderSize), inorderSize - idx - 1, list_slice(postorder, idx, postorderSize - 1),
                                postorderSize - idx - 1);

        return tree;
}

int main() {
        int inorder[5] = {9, 3, 15, 20, 7};
        int postorder[5] = {9, 15, 7, 20, 3};

        buildTree(inorder, 5, postorder, 5);

        return 0;
}
