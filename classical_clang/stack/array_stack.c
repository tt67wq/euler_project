/*
 * =====================================================================================
 *
 *       Filename:  array_stack.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

/* 栈的数组实现 */

#include <stdio.h>
#include <stdlib.h>

#define MINSIZE 64
#define MAXSIZE 4096

typedef struct _stack {
        int *data;
        int size;
        int top;
} stack;

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

int main() { return 0; }
