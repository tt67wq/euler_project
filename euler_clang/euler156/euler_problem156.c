/*
 * =====================================================================================
 *
 *       Filename:  euler_problem156.c
 *
 *    Description:  欧拉计划156题
 *
 *        Version:  1.0
 *        Created:  2018-08-23
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

typedef unsigned long long ull;

void count_digits(ull num, ull *counter) {
        while (num > 0) {
                counter[num % 10]++;
                num /= 10;
        }
}

ull ten_base_count(int m, int n, int b) {
        if (m == 1) {
                if (b != 1)
                        return pow(10, n - 1) * n;
                else
                        return pow(10, n - 1) * n + 1;
        } else {
                if (m > b)
                        return pow(10, n - 1) * n * m + pow(10, n);
                else if (m == b)
                        return pow(10, n - 1) * n * m + 1;
                else
                        return pow(10, n - 1) * n * m;
        }
}

int main() {
        ull counter[10] = {0};
        for (ull i = 1; i < 1000000; i++) {
                count_digits(i, counter);
                /* for (int j = 1; j < 10; j++) */
                /*         if (counter[j] == i) */
                /*                 printf("f(%llu, %d) = %llu\n", i, j, i); */
                if (i % 100000 == 0)
                        for (int j = 1; j < 10; j++) {
                                printf("f(%llu, %d) = %llu\n", i, j, counter[j]);
                                printf("f(%llu, %d) = %llu\n", i, j,
                                       ten_base_count(i / 100000, 5, j));
                        }
        }

        return 0;
}
