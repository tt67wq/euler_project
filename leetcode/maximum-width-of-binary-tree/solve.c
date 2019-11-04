/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-04
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

typedef struct _List {
        int size;
        int p;
        int *buffer;
} List;

void dfs(struct TreeNode *tr, int level, unsigned int index, List *acc, int *w) {
        if (tr == NULL)
                return;

        int tmp;

        if (level > acc->p) {
                acc->buffer[acc->p++] = index;
                if ((float)acc->p / acc->size > 0.8) {
                        acc->size <<= 1;
                        acc->buffer = (int *)realloc(acc->buffer, sizeof(int) * (acc->size));
                }
        }

        tmp = index - acc->buffer[level - 1] + 1;

        *w = *w > tmp ? *w : tmp;
        dfs(tr->left, level + 1, index * 2, acc, w);
        dfs(tr->right, level + 1, index * 2 + 1, acc, w);
}

int widthOfBinaryTree(struct TreeNode *root) {
        int w = 0;
        List *acc;
        acc = (List *)calloc(1, sizeof(List));
        acc->size = 1024;
        acc->p = 0;
        acc->buffer = (int *)calloc(acc->size, sizeof(int));
        dfs(root, 1, 1, acc, &w);

        free(acc->buffer);
        free(acc);

        return w;
}

int main() {
        int s = 10;
        s <<= 1;
        printf("%d\n", s);
        return 0;
}
