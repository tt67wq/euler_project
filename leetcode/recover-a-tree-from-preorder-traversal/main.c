/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-16
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

#define DEBUG
/* Definition for a binary tree node. */
typedef struct TreeNode Node;
struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

Node *recoverFromPreorderWithPrefix(char *S, int level);

void display(Node *t, int level) {

        if (t == NULL) {
                return;
        }
        for (int i = 0; i < level; i++) {
                printf("-");
        }
        printf("%d", t->val);
        display(t->left, level + 1);
        display(t->right, level + 1);
}

struct TreeNode *recoverFromPreorder(char *S) {
        return recoverFromPreorderWithPrefix(S, 0);
}

/* 1-2--3--4-5--6--7 */
/* 1-2--3---4-5--6---7 */
Node *recoverFromPreorderWithPrefix(char *S, int level) {
#ifdef DEBUG
        printf("orign: %s\n", S);
#endif
        char *s = S;
        while (*s == '-') {
                s++;
        }
        if (*s == '\0') {
                return NULL;
        }
        Node *tree = (Node *)malloc(sizeof(Node));
        tree->val = 0;
        while (*s != '-' && *s != '\0') {
                tree->val = tree->val * 10 + (*s) - '0';
                s++;
        }

        if (*s == '\0') {
                tree->left = NULL;
                tree->right = NULL;
                return tree;
        }
        char *left, *right, *s0;
        int n = 0, m = 0;
        s0 = s;

        while (*s == '-') {
                s++;
        }
#ifdef DEBUG
        printf("before searching: %s\n", s);
#endif

        // search right
        while (*s != '\0') {
                if (*s == '-') {
                        n++;
                } else {
                        if (n == level + 1) {
                                break;
                        } else {
                                n = 0;
                        }
                }
                s++;
                m++;
        }
#ifdef DEBUG
        printf("after searching: %s\n", s);
#endif

        if (*s == '\0') {
                tree->right = NULL;
                tree->left = recoverFromPreorderWithPrefix(s0, level + 1);
        } else {
                right = s - level - 1;
                tree->right = recoverFromPreorderWithPrefix(right, level + 1);
                left = (char *)malloc((m + 1) * sizeof(char));
                strncpy(left, s0, (m) * sizeof(char));
                *(left + m) = '\0';

                tree->left = recoverFromPreorderWithPrefix(left, level + 1);
                free(left);
        }

        return tree;
}

int main() {

        /* Node *t = recoverFromPreorder("1-2--3--4-5--6--7"); */
        Node *t = recoverFromPreorder("1-2--3---4-5--6---7");
        /* Node *t = recoverFromPreorder("1-401--349---90--88"); */
        display(t, 0);
        return 0;
}
