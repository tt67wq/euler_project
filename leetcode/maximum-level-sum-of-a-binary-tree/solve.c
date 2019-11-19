/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-19
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

#define MAX 1000

struct TreeNode {
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
};

typedef struct _queue {
        int front;
        int rear;
        int size;
        struct TreeNode **buff;
} queue;

void init(queue *q) {
        q->front = 0;
        q->rear = 0;
        q->size = 0;
        q->buff = (struct TreeNode **)calloc(MAX, sizeof(struct TreeNode *));
}

void drop(queue *q) {
        free(q->buff);
        free(q);
}

bool is_full(queue *q) { return q->size == MAX; }
bool is_empty(queue *q) { return q->size == 0; }

bool enqueue(queue *q, struct TreeNode *elem) {
        if (is_full(q))
                return false;
        q->buff[q->rear] = elem;
        q->rear = (q->rear + 1) % MAX;
        q->size++;
        return true;
}

bool dequeue(queue *q, struct TreeNode **elem) {
        if (is_empty(q))
                return false;
        *elem = q->buff[q->front];
        q->front = (q->front + 1) % MAX;
        q->size--;
        return true;
}

int maxLevelSum(struct TreeNode *root) {
        if (root == NULL)
                return 0;

        queue *q;
        int i, sum_max, level, level_max, curr_sum, size;
        struct TreeNode *tmp;

        q = (queue *)calloc(1, sizeof(queue));
        init(q);

        sum_max = root->val;
        level = 1;
        level_max = 1;

        enqueue(q, root);
        while (!is_empty(q)) {
                curr_sum = 0;
                size = q->size;
                for (i = 0; i < size; i++) {
                        dequeue(q, &tmp);
                        curr_sum += tmp->val;
                        if (tmp->left != NULL)
                                enqueue(q, tmp->left);
                        if (tmp->right != NULL)
                                enqueue(q, tmp->right);
                }
		printf("%d\n", curr_sum);
                if (curr_sum > sum_max) {
                        sum_max = curr_sum;
                        level_max = level;
                }
                level++;
        }
        drop(q);
        return level_max;
}

int main() { return 0; }
