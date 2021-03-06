/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-05
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

int calPoints(char **ops, int opsSize) {
        stack *st;
        int i, r = 0;

        st = new_stack();
        for (i = 0; i < opsSize; i++) {
                /* printf("%s %d %d\n", ops[i], st->top, st->size); */
                if (strcmp(ops[i], "C") == 0) {
                        pop(st);
                        continue;
                }
                if (strcmp(ops[i], "D") == 0) {
                        push(st, st->data[st->top] * 2);
                        continue;
                }
                if (strcmp(ops[i], "+") == 0) {
                        push(st, st->data[st->top] + st->data[st->top - 1]);
                        continue;
                }
                push(st, atoi(ops[i]));
        }

        while (st->top > -1)
                r += pop(st);

        release_stack(st);
        return r;
}

int main() {
        char *ops[20] = {"35", "-32", "C", "39", "+", "-48", "C", "5", "88", "-52", "+", "C", "D", "D", "100", "C", "+", "-74", "53", "59"};

        printf("%d\n", calPoints(ops, 20));

        return 0;
}
