/*
 * =====================================================================================
 *
 *       Filename:  euler_problem37.c
 *
 *    Description:  欧拉计划37题
 *
 *        Version:  1.0
 *        Created:  2018-09-04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "prime.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int check(ull num) {
        if (num < 10)
                return 0;
        ull tmp = num;
        while (tmp > 0) {
                int r = tmp % 10;
                if (r % 2 == 0 || r == 5)
                        return 0;
                tmp /= 10;
        }
        return 1;
}

int double_check(ull num) {
        ull tmp = num;
        while (tmp) {
                if (!probablyPrime(tmp, 3))
                        return 0;

                tmp /= 10;
        }
        return 1;
}

int triple_check(ull num) {
        ull tmp = num;
        ull p = 0;
        while (tmp) {
                tmp /= 10;
                p++;
        }

        while (p) {
                if (!probablyPrime(num % (int)(pow(10, p)), 3))
                        return 0;
                p--;
        }
        return 1;
}

int main() {
        clock_t begin = clock();
        int count = 0;
        ull i = 1;
        ull sum = 0;
        while (1) {
                if (count == 11)
                        break;
                if (i++ < 10)
                        continue;
                /* if (check(i)) { */
                if (probablyPrime(i, 3))
                        if (double_check(i))
                                if (triple_check(i)) {
                                        printf("%llu\n", i);
                                        count++;
                                        sum += i;
                                }

                i++;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %llu time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        exit(EXIT_SUCCESS);
}
