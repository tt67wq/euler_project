/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MINSIZE 64
#define MAXSIZE 4096
#define DEBUG

typedef struct _stack stack;
struct _stack {
        int *data;
        int size;
        int top;
};

#define STACK_TOP(st) ((st)->data[(st)->top])
#define IS_EMPTY(st) ((st)->top == -1)

stack *new_stack() {
        stack *st;
        st = (stack *)calloc(1, sizeof(stack));
        st->top = -1;
        st->size = 64;
        st->data = (int *)calloc(st->size, sizeof(int));
        return st;
}

void release_stack(stack *st) {
        if (st != NULL) {
                free(st->data);
                free(st);
        }
}

void push(stack *st, int item) {
        st->data[++st->top] = item;
        if ((float)st->top / st->size > 0.8 && st->size < MAXSIZE) {
                st->size <<= 1;
                st->data = (int *)realloc(st->data, sizeof(int) * st->size);
        }
}

int pop(stack *st) {
        int r;
        r = st->data[st->top--];
        if ((float)st->top / st->size < 0.3 && st->size > MINSIZE) {
                st->size >>= 1;
                st->data = (int *)realloc(st->data, sizeof(int) * st->size);
        }
        return r;
}

int longestWPI(int *hours, int hoursSize) {

        // 归一化
        for (int i = 0; i < hoursSize; i++) {
                if (hours[i] > 8) {
                        hours[i] = 1;
                } else {
                        hours[i] = -1;
                }
        }

        // 前缀
        int *sums = (int *)calloc(hoursSize + 1, sizeof(int));

        for (int i = 1; i <= hoursSize; i++) {
                sums[i] = sums[i - 1] + hours[i - 1];
        }
#ifdef DEBUG
        printf("前缀和: \n");
        for (int i = 0; i <= hoursSize; i++) {
                printf("%d ", sums[i]);
        }
        printf("\n");
#endif

        // 单调递减栈
        stack *st = new_stack();

        for (int i = 0; i < hoursSize + 1; i++) {
                if (IS_EMPTY(st) || sums[STACK_TOP(st)] > sums[i]) {
#ifdef DEBUG
                        printf("压入%d\n", i);
#endif
                        push(st, i);
                }
        }

	// 计算最长坡
        int ans = 0;
        for (int i = hoursSize; i > ans && !IS_EMPTY(st); i--) {
                while (!IS_EMPTY(st) && sums[STACK_TOP(st)] < sums[i]) {
                        int tmp = i - STACK_TOP(st);
                        if (tmp > 0)
                                ans = ans > tmp ? ans : tmp;
                        pop(st);
                }
        }

        release_stack(st);
        free(sums);

        return ans;
}

int main() {
        int hours[] = {6, 9, 9};
        printf("%d\n", longestWPI(hours, 3));
        return 0;
}
