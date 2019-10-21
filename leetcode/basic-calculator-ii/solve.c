/*
 * =====================================================================================
 *
 *       Filename:  solve.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

typedef struct _elem {
        char sign;
        int val;
} elem;

typedef struct _Stack {
        elem data[MAX];
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

int calculate(char *s) {
        int i = 0, j = 0;
        int l;
        char sign;
        char buffer[10] = {0};
        elem item;
        Stack *st;
        int res = 0;

        sign = '+';
        l = strlen(s);
        st = NewStack();

        while (i < l) {
                /* printf("buffer = %s\n", buffer); */
                if (s[i] == ' ') {
                        i++;
                        continue;
                }

                if (s[i] == '+' | s[i] == '-' | s[i] == '*' | s[i] == '/') {

                        if (sign == '*') {
                                item = Pop(st);
                                item.val *= atoi(buffer);
                                Push(st, item);

                                // reset buffer
                                bzero(buffer, sizeof(char) * 10);
                                j = 0;

                                sign = s[i++];
                                continue;
                        }

                        if (sign == '/') {
                                item = Pop(st);
                                item.val /= atoi(buffer);
                                Push(st, item);

                                // reset buffer
                                bzero(buffer, sizeof(char) * 10);
                                j = 0;

                                sign = s[i++];
                                continue;
                        }

                        item.sign = sign;
                        item.val = atoi(buffer);
                        sign = s[i++];

                        // push to stack
                        Push(st, item);

                        // reset buffer
                        bzero(buffer, sizeof(char) * 10);
                        j = 0;
                        continue;
                }

                buffer[j++] = s[i++];
        }

        // rest
        if (sign == '*') {
                item = Pop(st);
                item.val *= atoi(buffer);
                Push(st, item);
        }
        if (sign == '/') {
                item = Pop(st);
                item.val /= atoi(buffer);
                Push(st, item);
        }
        if (sign == '+' | sign == '-') {
                item.sign = sign;
                item.val = atoi(buffer);
                Push(st, item);
        }

        while (st->top > -1) {
                item = Pop(st);
                /* printf("%c%d\n", item.sign, item.val); */
                if (item.sign == '+')
                        res += item.val;
                else
                        res -= item.val;
        }
        ReleaseStack(st);
        return res;
}

int main() {
        char line[100];
        while (1) {
                fgets(line, 100, stdin);
                printf("%s = %d\n", line, calculate(line));
        }
        return 0;
}
