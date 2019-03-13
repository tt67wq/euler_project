/*
 * =====================================================================================
 *
 *       Filename:  euler61.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-13
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
#include <time.h>
#define MAX 10000

char *series[6];
int match[6], seq[6], count = 0;
char *desc[6];

#define GEN(n, f)                                                                                                                                                                                     \
        series[n] = gen(f);                                                                                                                                                                           \
        desc[n] = #f;

int triangle(int n) { return n * (n + 1) * 0.5; }
int square(int n) { return n * n; }
int pentagonal(int n) { return n * (3 * n - 1) * 0.5; }
int hexagonal(int n) { return n * (2 * n - 1); }
int heptagonal(int n) { return n * (5 * n - 3) * 0.5; }
int octagonal(int n) { return n * (3 * n - 2); }

char *gen(int (*f)(int)) {
        int N, n;
        char *a = (char *)calloc(MAX + 1, sizeof(char));
        for (n = 1;; n++) {
                N = f(n);
                if (N >= MAX)
                        break;
                a[N]++;
        }
        return a;
}
void foo(int rs, int re) {
        int i, n, nrs;
        char s[5];
        count++;
        if (count > 6) {
                for (i = 0; i < 6; i++) {
                        if (!match[i])
                                break;
                }
                if (i == 6) {
                        if (seq[0] / 100 == seq[5] % 100) {
                                for (i = 0; i < 6; i++)
                                        printf("%04d ", seq[i]);
                                printf("\n");
                                printf("%d\n", seq[0] + seq[1] + seq[2] + seq[3] + seq[4] + seq[5]);
                                return;
                        }
                }
                count--;
                return;
        }
        for (i = rs; i < re; i++) {
                for (n = 0; n < 6; n++) {
                        if (series[n][i]) {
                                if (!match[n]) {
                                        match[n] = i;
                                        sprintf(s, "%d", i);
                                        nrs = strtol(s + 2, 0, 10) * 100;
                                        if (nrs >= 1000) {
                                                seq[count - 1] = i;
                                                foo(nrs, nrs + 100);
                                        }
                                        match[n] = 0;
                                        seq[count - 1] = 0;
                                }
                        }
                }
        }
        count--;
}
int main() {
        clock_t begin = clock();
        GEN(0, triangle);
        GEN(1, square);
        GEN(2, pentagonal);
        GEN(3, hexagonal);
        GEN(4, heptagonal);
        GEN(5, octagonal);
        memset(match, 0, 6 * sizeof(int));
        foo(1000, 10000);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
