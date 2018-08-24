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

int main() {
        ull sum = 0;
        ull counter[10] = {0};
        for (ull i = 1; i < 1000000; i++) {
                count_digits(i, counter);
                /* for (int j = 1; j < 10; j++) { */
                /*         if (counter[j] == i) { */
                /*                 printf("f(%llu, %d) = %llu\n", i, j, i); */
                /*                 sum += i; */
                /*         } */
                /* } */
                /* if (i == 9999999 || i == 999999 || i == 99999 || i == 9999 || i == 999 || */
                /*     i == 99 || i == 9) { */
                /*         /\* for (int j = 1; j < 10; j++) *\/ */
                /*         printf("f(%llu, %d) = %llu\n", i, 1, counter[1]); */
                /* } */

                if (i % 100000 == 0)
                        printf("f(%llu, %d) = %llu\n", i, 1, counter[1]);

                /* if (i == 221902 || i == 21902 || i == 200000) */
                /*         printf("f(%llu, %d) = %llu\n", i, 7, counter[7]); */
        }

        return 0;
}
