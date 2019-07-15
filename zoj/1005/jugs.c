/*
 * =====================================================================================
 *
 *       Filename:  jugs.c
 *
 *    Description:  zoj 1005
 *
 *        Version:  1.0
 *        Created:  2019-07-15
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

#define FULLA 1
#define FULLB 2
#define EMPTYA 3
#define EMPTYB 4
#define A2B 5
#define B2A 6
#define MAX 1000

typedef struct _state {
        int move;
        int a;
        int b;
} state;

int CA;
int CB;
int N;
state *MOVES;
char (*CACHE)[10];

char cache_hit(int a, int b) {
        int i;
        char buf[10];
        sprintf(buf, "%d:%d", a, b);
        for (i = 0; i < MAX; i++) {
                if (CACHE[i] == 0)
                        return 0;
                if (strcmp(buf, CACHE[i]) == 0)
                        return 1;
        }
        return 0;
}

void set_cache(int a, int b) {
        int i;
        char buf[10];
        char empty[10] = {0};
        sprintf(buf, "%d:%d", a, b);
        for (i = 0; i < MAX; i++) {
                if (strcmp(CACHE[i], empty) == 0) {
                        strcpy(CACHE[i], buf);
                        break;
                }
        }
}

void solve(int a, int b) {
        int m, d, index = 0;
        state tmp;
        while (a != N && b != N) {
                printf("%d %d %d\n", a, b, index);
                for (m = 1; m <= 6; m++) {
                        if (m == FULLA) {
				printf("%d\n", m);
                                if (a == CA)
                                        continue;
                                if (cache_hit(CA, b))
                                        continue;

                                a = CA;
                                set_cache(a, b);
                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;
                                break;
                        }
                        if (m == FULLB) {
                                if (b == CB)
                                        continue;
                                if (cache_hit(a, CB))
                                        continue;

                                b = CB;
                                set_cache(a, b);
                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;

                                break;
                        }
                        if (m == EMPTYA) {
                                if (a == 0)
                                        continue;
                                if (cache_hit(0, b))
                                        continue;

                                a = 0;
                                set_cache(a, b);
                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;

                                break;
                        }

                        if (m == EMPTYB) {
                                if (b == 0)
                                        continue;
                                if (cache_hit(a, 0))
                                        continue;

                                b = 0;
                                set_cache(a, b);
                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;

                                break;
                        }
                        if (m == A2B) {
                                if (a == 0 || b == CB)
                                        continue;
                                d = (CB - b) > a ? a : CB - b;
                                if (cache_hit(a - d, b + d))
                                        continue;

                                a -= d;
                                b += d;
                                set_cache(a, b);

                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;

                                break;
                        }
                        if (m == B2A) {
                                if (b == 0 || a == CA)
                                        continue;
                                d = CA - a > b ? b : CA - a;
                                if (cache_hit(a + d, b - d))
                                        continue;

                                a += d;
                                b -= d;
                                set_cache(a, b);

                                tmp.move = m;
                                tmp.a = a;
                                tmp.b = b;
                                MOVES[index++] = tmp;

                                break;
                        }
                }
        }
}

int main() {
        int i;
        while (scanf("%d %d %d", &CA, &CB, &N) != EOF) {
                MOVES = (state *)calloc(1000, sizeof(state));
                CACHE = (char(*)[10])calloc(1000, sizeof(char[10]));
                solve(0, 0);
                for (i = 0; i < MAX; i++) {
                        if (MOVES[i].move == 0)
                                break;
                        if (MOVES[i].move == FULLA)
                                printf("fill A: %d, %d\n", MOVES[i].a, MOVES[i].b);
                        else if (MOVES[i].move == FULLB)
                                printf("fill B: %d, %d\n", MOVES[i].a, MOVES[i].b);
                        else if (MOVES[i].move == EMPTYA)
                                printf("empty A: %d, %d\n", MOVES[i].a, MOVES[i].b);
                        else if (MOVES[i].move == EMPTYB)
                                printf("empty B: %d, %d\n", MOVES[i].a, MOVES[i].b);
                        else if (MOVES[i].move == A2B)
                                printf("pour A B: %d, %d\n", MOVES[i].a, MOVES[i].b);
                        else if (MOVES[i].move == B2A)
                                printf("pour B A: %d, %d\n", MOVES[i].a, MOVES[i].b);
                }
                free(MOVES);
                free(CACHE);
                printf("success\n");
        }
        return 0;
}
