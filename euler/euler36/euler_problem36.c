/*
 * =====================================================================================
 *
 *       Filename:  euler_problem36.c
 *
 *    Description:  欧拉计划36题
 *
 *        Version:  1.0
 *        Created:  2018-09-03
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

#define LIMIT 1000000

typedef unsigned long long ull;

// 十进制到二进制
ull d2b(ull num) {
        ull res = 0;
        int l = 0;
        int temp[20] = {0};
        while (num) {
                temp[l++] = num % 2;
                num /= 2;
        }

        for (int i = l; i >= 0; i--)
                res = res * 10 + temp[i];

        return res;
}

int palindromic(ull num) {
        int temp[20] = {0};
        int l = 0;
        while (num) {
                temp[l++] = num % 10;
                num /= 10;
        }
        /* for (int i = 0; i < l; i++) */
        /*         printf("%d", temp[i]); */
        /* printf("\n"); */
        for (int i = 0; i < l; i++) {
                int j = l - 1 - i;
                /* printf("i => %d, j => %d, temp[i] => %d, temp[j] => %d\n", i, j, temp[i],
                 * temp[j]); */
                if (temp[i] == temp[j])
                        continue;
                else
                        return 0;
        }
        return 1;
}

int main() {
        clock_t begin = clock();
        ull sum = 0;
        for (ull i = 1; i < LIMIT; i++) {
                if (i % 2 == 0)
                        continue;
                else {
                        if (palindromic(i) && palindromic(d2b(i))) {
                                printf("%llu\n", i);
                                sum += i;
                        }
                }
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %llu time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));
        exit(EXIT_SUCCESS);
}
