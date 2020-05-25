/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-25
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

#define DEBUG
#define MAX_SIZE 1000
/* Definition for a binary tree node. */
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

typedef struct TreeNode Node;

bool canPalindromic(int *box, int size) {
        int vis[10] = {0};
        for (int i = 0; i < size; i++) {
                vis[box[i]] += 1;
        }
        int odds = 0;
        for (int i = 1; i < 10; i++) {
                if (vis[i] & 1) {
                        odds++;
                }
        }
        return odds <= 1;
}

void dfs(Node *root, int *box, int size, int *palinSize) {
        if (root->left == NULL && root->right == NULL) {
                box[size] = root->val;
#ifdef DEBUG
                for (int i = 0; i <= size; i++) {
                        printf("%d ", box[i]);
                }
                printf("\n");
#endif
                if (canPalindromic(box, size + 1)) {
                        (*palinSize)++;
                }
                return;
        }

        box[size] = root->val;
        if (root->left != NULL)
                dfs(root->left, box, size + 1, palinSize);
        if (root->right != NULL)
                dfs(root->right, box, size + 1, palinSize);
}

int pseudoPalindromicPaths(struct TreeNode *root) {
        int *box = (int *)calloc(MAX_SIZE, sizeof(int));
        int ans = 0;
        dfs(root, box, 0, &ans);
        free(box);
        return ans;
}

int main() { return 0; }
