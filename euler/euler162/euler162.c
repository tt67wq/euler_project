/*
 * =====================================================================================
 *
 *       Filename:  euler162.c
 *
 *    Description:  欧拉计划162题
 *
 *        Version:  1.0
 *        Created:  2018-11-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <time.h>

long long c(int n, int d) {
        if (d > n)
                return 0;
        if (n == 1 && d == 1)
                return 1;
        if (d == 0)
                return 16ll << (4 * (n - 1));
        return d * c(n - 1, d - 1) + (16 - d) * c(n - 1, d);
}

int main(void) {
        clock_t begin = clock();
        long long s = 0;
        int i;

        for (i = 3; i <= 16; i++)
                s += 2 * c(i - 1, 2) + 13 * c(i - 1, 3);
        printf("%llX\n", s);

        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
