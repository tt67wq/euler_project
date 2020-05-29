/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-29
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

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

#define DEBUG
#define MAX 10000

char *smallestFromLeaf(struct TreeNode *root) {}

struct TreeNode new (int val) {
        struct TreeNode n;
        n.val = val;
        n.left = NULL;
        n.right = NULL;
        return n;
}

int main() {
        /* [2,2,1,null,1,0,null,0] */
        struct TreeNode n0 = new (4);
        struct TreeNode n1 = new (0);
        struct TreeNode n2 = new (1);
        struct TreeNode n3 = new (1);
        /* struct TreeNode n4 = new (0); */
        /* struct TreeNode n5 = new (0); */

        n0.left = &n1;
        n0.right = &n2;
        n1.right = &n3;

        char *ans = smallestFromLeaf(&n0);
        printf("%s\n", ans);
        free(ans);

        return 0;
}
