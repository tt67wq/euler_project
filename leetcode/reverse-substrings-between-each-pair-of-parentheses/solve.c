/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pair {
        char val;
        int pos;
} pair;

typedef struct _Stack {
        pair data[1000];
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

void Push(Stack *stack, pair item) { stack->data[++stack->top] = item; }

pair Pop(Stack *stack) { return stack->data[stack->top--]; }

void reverse_bw(char *s, int start, int end) {
        int i, j;
        char tmp;
        i = start;
        j = end;
        while (i <= j - 1) {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
                i++;
                j--;
        }
}

char *reverseParentheses(char *s) {
        int i, j, l;
        pair item;
        Stack *st;
        char *r;

        l = strlen(s);
        st = NewStack();
        for (i = 0; i < l; i++) {
                if (s[i] == '(') {
                        item.pos = i;
                        item.val = '(';
                        Push(st, item);
                        continue;
                } else if (s[i] == ')') {
                        // 检查栈顶
                        if (st->data[st->top].val == '(') {
                                item = Pop(st);
                                reverse_bw(s, item.pos, i);
                        } else {
                                item.pos = i;
                                item.val = ')';
                                Push(st, item);
                        }
                        continue;
                } else {
                        ;
                }
        }
        ReleaseStack(st);

        r = (char *)calloc(l + 1, sizeof(char));
        j = 0;
        for (i = 0; i < l; i++) {
                if (s[i] == '(' | s[i] == ')') {
                        ;
                } else {
                        r[j] = s[i];
                        j++;
                }
        }
        return r;
}

int main() {

        char s[100];
        char *res;
        while (1) {
                scanf("%s", s);
                res = reverseParentheses(s);
                printf("%s\n", res);
        }

        return 0;
}
