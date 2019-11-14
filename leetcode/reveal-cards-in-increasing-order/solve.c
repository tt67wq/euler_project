/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-14
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

typedef struct _node {
        int val;
        struct _node *previous;
        struct _node *next;
} node;

typedef struct _dq {
        int size;
        node *head;
        node *tail;
} dq;

void left_push(dq *q, int val) {
        node *t;

        t = (node *)calloc(1, sizeof(node));
        t->val = val;

        if (q->size == 0) {
                q->head = t;
                q->tail = t;
        } else {
                t->next = q->head;
                q->head->previous = t;
                q->head = t;
        }
        q->size++;
}

int right_pop(dq *q) {
        if (q->size == 0) {
                printf("pop from an empty queue!\n");
                return 0;
        }
        int a;
        node *t;

        t = q->tail;
        a = t->val;

        if (q->size == 1) {
                q->head = NULL;
                q->tail = NULL;
        } else {
                q->tail = q->tail->previous;
                q->tail->next = NULL;
        }
        free(t);
        q->size--;

        return a;
}

void swap(int *a, int *b) {
        int temp;

        temp = *a;
        *a = *b;
        *b = temp;

        return;
}

void quick_sort(int *array, int begin, int end) {
        int i, j;
        if (begin < end) {
                i = begin + 1;
                j = end;
                while (i < j) {
                        if (array[i] < array[begin]) {
                                swap(&array[i], &array[j]);
                                j--;
                        } else {
                                i++;
                        }
                }

                if (array[i] <= array[begin])
                        i--;

                swap(&array[begin], &array[i]);
                quick_sort(array, begin, i);
                quick_sort(array, j, end);
        }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *deckRevealedIncreasing(int *deck, int deckSize, int *returnSize) {
        int *ans, i, t;
        dq *q;

        ans = (int *)calloc(deckSize, sizeof(int));
        q = (dq *)calloc(1, sizeof(dq));
        q->size = 0;

        quick_sort(deck, 0, deckSize - 1);

        left_push(q, deck[0]);
        for (i = 1; i < deckSize; i++) {
                t = right_pop(q);
                /* printf("a: push %d\n", t); */
                left_push(q, t);
                /* printf("b: push %d\n", deck[i]); */
                left_push(q, deck[i]);
        }

        while (q->size > 0)
                ans[--i] = right_pop(q);

        *returnSize = deckSize;

        free(q);
        return ans;
}

int main() {
        int deck[] = {17, 13, 11, 2, 3, 5, 7};
        int *ans, size, i;

        ans = deckRevealedIncreasing(deck, 7, &size);

        for (i = 0; i < size; i++) {
                printf("%d ", ans[i]);
        }
        printf("\n");
        free(ans);
        return 0;
}
