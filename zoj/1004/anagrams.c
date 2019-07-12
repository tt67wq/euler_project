/*
 * =====================================================================================
 *
 *       Filename:  anagrams.c
 *
 *    Description:  zoj 1004
 *
 *        Version:  1.0
 *        Created:  2019-07-12
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

#define MAXSIZE 500

char FROM[MAXSIZE];
char TO[MAXSIZE];
char PATH[MAXSIZE];

typedef struct _stack {
        char *data;
        int top;
} stack;

void init(stack *s) {
        s->data = (char *)calloc(MAXSIZE, sizeof(char));
        s->top = 0;
}

void drop(stack *s) { free(s->data); }
void push(char e, stack *s) {
        s->top++;
        s->data[s->top] = e;
}

char pop(stack *s) {
        char e;
        e = s->data[s->top];
        s->top--;
        return e;
}

char match(int size) {
        stack *s = (stack *)calloc(1, sizeof(stack));
        int i = 0, j = 0, k = 0;
        char m;

        init(s);
        char *buff = (char *)calloc(size, sizeof(char));

        while (i < (size << 1)) {
                m = PATH[i++];

                if (m == 'i') {
                        push(FROM[j], s);
                        j++;
                } else {
                        buff[k] = pop(s);
                        k++;
                }
        }
        if (strcmp(buff, TO) == 0) {
                free(buff);
                drop(s);
                return 1;
        } else {
                free(buff);
                drop(s);
                return 0;
        }
}

void solve(int size, int is, int os, int index) {
        if (os == size) {
                if (match(size)) {
                        int i;
                        for (i = 0; i < (size << 1); i++) {
                                printf("%c ", PATH[i]);
                        }
                        printf("\n");
                }

                return;
        }

        if (is == size) {
                PATH[index] = 'o';
                solve(size, is, os + 1, index + 1);
        } else if (is == os) {
                PATH[index] = 'i';
                solve(size, is + 1, os, index + 1);
        } else {
                PATH[index] = 'i';
                solve(size, is + 1, os, index + 1);
                PATH[index] = 'o';
                solve(size, is, os + 1, index + 1);
        }
        return;
}

int main() {

        while (scanf("%s\n%s", FROM, TO) != EOF) {
                if (strlen(FROM) != strlen(TO)) {
                        printf("[\n]\n");
                } else {
                        printf("[\n");
                        solve((int)strlen(FROM), 0, 0, 0);
                        printf("]\n");
                }
        }
        return 0;
}
