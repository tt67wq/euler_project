/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-03-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct Node {
        int val;
        struct Node *left;
        struct Node *right;
        struct Node *next;
};

struct item {
        struct Node *node;
        SIMPLEQ_ENTRY(item) ptr;
};

SIMPLEQ_HEAD(qhead, item);

struct qhead *q0, *q1;

struct Node *connect(struct Node *root) {
        if (!root) {
                return NULL;
        }
        q0 = (struct qhead *)malloc(sizeof(struct qhead));
        q1 = (struct qhead *)malloc(sizeof(struct qhead));

        SIMPLEQ_INIT(q0);
        SIMPLEQ_INIT(q1);

        struct item *tmp = (struct item *)malloc(sizeof(struct item));
        tmp->node = root;
        SIMPLEQ_INSERT_TAIL(q0, tmp, ptr);

        while (!SIMPLEQ_EMPTY(q0)) {
                struct item *tmp = SIMPLEQ_FIRST(q0);
                SIMPLEQ_REMOVE_HEAD(q0, ptr);
                if (SIMPLEQ_FIRST(q0)) {
                        tmp->node->next = SIMPLEQ_FIRST(q0)->node;
                } else {
                        tmp->node->next = NULL;
                }

                if (tmp->node->left) {
                        struct item *lc = (struct item *)malloc(sizeof(struct item));
                        lc->node = tmp->node->left;
                        SIMPLEQ_INSERT_TAIL(q1, lc, ptr);
                }
                if (tmp->node->right) {
                        struct item *rc = (struct item *)malloc(sizeof(struct item));
                        rc->node = tmp->node->right;
                        SIMPLEQ_INSERT_TAIL(q1, rc, ptr);
                }

                if (SIMPLEQ_EMPTY(q0)) {
                        if (!SIMPLEQ_EMPTY(q1)) {
                                q0 = q1;
                                q1 = (struct qhead *)malloc(sizeof(struct qhead));
                                SIMPLEQ_INIT(q1);
                        } else {
                                break;
                        }
                }
        }
        return root;
}

int main() {
        // struct Node n1, n2, n3, n4, n5, n6, n7;
        // n1.val = 1;
        // n2.val = 2;
        // n3.val = 3;
        // n4.val = 4;
        // n5.val = 5;
        // n6.val = 6;
        // n7.val = 7;

        // n1.left = &n2;
        // n1.right = &n3;
        // n2.left = &n4;
        // n2.right = &n5;
        // n3.left = &n6;
        // n3.right = &n7;
        // n4.left = NULL;
        // n4.right = NULL;
        // n5.left = NULL;
        // n5.right = NULL;
        // n6.left = NULL;
        // n6.right = NULL;
        // n7.left = NULL;
        // n7.right = NULL;

        connect(NULL);

        return 0;
}