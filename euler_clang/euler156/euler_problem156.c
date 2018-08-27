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
ull ten_base_count(int, int, int);

void count_digits(ull num, ull *counter) {
        while (num > 0) {
                counter[num % 10]++;
                num /= 10;
        }
}

ull count_digits2(ull num, int base) {
        ull tmp = num;
        int p = 0;
        ull count = 0;
        while (tmp > 0) {
                tmp /= 10;
                p++;
        }
        while (p >= 0) {
                ull n = (ull)pow(10, p);
                count += ten_base_count((int)(num / n), p, base);
                if ((int)(num / n) == base)
                        count += num % n;
                num %= n;
                p--;
        }
        return count;
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
        /* ull counter[10] = {0}; */
        /* for (ull i = 1; i < 1000000; i++) { */
        /*         count_digits(i, counter); */
        /*         for (int j = 1; j < 10; j++) */
        /*                 if (counter[j] == i) { */
        /*                         printf("f(%llu, %d) = %llu\n", i, j, i); */
        /*                 } */
        /* } */
        for (ull i = 1; i < 10000000000; i++) {
                ull tmp = count_digits2(i, 1);
                if (tmp == i)
                        printf("f(%llu, %d) = %llu\n", i, 1, tmp);
        }

        /* for (int j = 1; j < 10; j++) { */
        /*         ull tmp = count_digits2(i, j); */
        /*         if (tmp == i) */
        /*                 printf("f(%llu, %d) = %llu\n", i, j, tmp); */
        /* } */

        return 0;
}
