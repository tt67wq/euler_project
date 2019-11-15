/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-15
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
#include <unistd.h>

#define MINSIZE 64
#define MAXSIZE 4096

typedef struct _stack {
        int *data;
        int size;
        int top;
} stack;

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

bool validateStackSequences(int *pushed, int pushedSize, int *popped, int poppedSize) {
        if (pushedSize != poppedSize)
                return false;
        if (pushedSize == 0)
                return true;

        stack *st;
        int i, j;
        bool ans;

        st = new_stack();

        i = 0;
        j = 0;
        while (j < poppedSize) {
                if (st->top > -1) {
                        /* 非空 */
                        if (st->data[st->top] != popped[j]) {
                                if (i >= pushedSize)
                                        break;
                                push(st, pushed[i++]);
                        } else {
                                j++;
                                pop(st);
                        }
                } else {
                        /* 空栈 */
                        for (; i < pushedSize; i++) {
                                push(st, pushed[i]);
                                if (pushed[i] == popped[j]) {
                                        i++;
                                        break;
                                }
                        }
                }
        }

        if (st->top == -1 && j == poppedSize)
                ans = true;
        else
                ans = false;

        release_stack(st);
        return ans;
}

bool testValidateStackSequences(int *pushed, int pushedSize, int *popped, int poppedSize) {
        if (pushedSize != poppedSize)
                return false;
        if (pushedSize == 0)
                return true;

        stack *st;
        int i, j;
        bool ans;

        st = new_stack();

        i = 0;
        j = 0;
        while (j < poppedSize) {
                if (st->top > -1) {
                        /* 非空 */
                        printf("栈顶 -> %d, popped[%d] = %d\n", st->data[st->top], j, popped[j]);
                        if (st->data[st->top] != popped[j]) {
                                if (i >= pushedSize)
                                        break;
                                printf("%d 入栈\n", pushed[i]);
                                push(st, pushed[i++]);
                        } else {
                                j++;
                                printf("%d 出栈\n", pop(st));
                        }
                } else {
                        /* 空栈 */
                        printf("此时为空栈\n");
                        for (; i < pushedSize; i++) {
                                printf("%d 入栈\n", pushed[i]);
                                push(st, pushed[i]);
                                if (pushed[i] == popped[j]) {
                                        i++;
                                        break;
                                }
                        }
                }
                sleep(1);
        }

        printf("栈体积 -> %d, j -> %d\n", st->top, j);
        if (st->top == -1 && j == poppedSize)
                ans = true;
        else
                ans = false;

        release_stack(st);
        return ans;
}

int main() {

        int pushed[] = {1, 2, 3, 4, 5};
        int popped[] = {4, 5, 3, 2, 1};

        printf("%d\n", validateStackSequences(pushed, 5, popped, 5));

        return 0;
}
