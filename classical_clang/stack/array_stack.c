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

typedef struct _elem {
        char val;
        int pos;
} elem;

typedef struct _Stack {
        elem data[1000];
        int top;
} Stack;

Stack *NewStack() {
        Stack *stack;
        stack = (Stack *)malloc(sizeof(Stack));
        stack->top = -1;
        return stack;
}

void ReleaseStack(Stack *S) {
        if (S != NULL) {
                free(S->data);
                /* free(S); */
        }
}

void Push(Stack *stack, elem item) { stack->data[++stack->top] = item; }

elem Pop(Stack *stack) { return stack->data[stack->top--]; }

elem Top(Stack *stack) { return stack->data[stack->top]; }

int main() { return 0; }
