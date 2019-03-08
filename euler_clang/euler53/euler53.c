/*
 * =====================================================================================
 *
 *       Filename:  euler53.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.1415926

double log_fact(int x) {
        double n = x;
        return n * log10(n) - n + log10(n * (1.0 + 4.0 * n * (1.0 + 2.0 * n))) / 6.0 + log10(PI) / 2.0f;
}

double log_combination(int n, int r) { return log_fact(n) - log_fact(r) - log_fact(n - r); }

int main() {
        clock_t begin = clock();

        double t = log10(1000000);
        int counter = 0;
        for (int n = 1; n <= 100; n++) {
                for (int r = 1; r < n; r++) {
                        if (log_combination(n, r) > t)
                                counter++;
                }
        }
        printf("%d\n", counter);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
