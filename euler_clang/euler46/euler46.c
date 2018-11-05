/*
 * =====================================================================================
 *
 *       Filename:  euler46.c
 *
 *    Description:  欧拉计划46题
 *
 *        Version:  1.0
 *        Created:  2018-11-05
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

#define LIMIT 1000

void find_primes(int *primes, int index, int pindex) {
        if (pindex > LIMIT)
                return;
        if (probablyPrime(index, 3))
                primes[pindex++] = index;

        index += 1;
        find_primes(primes, index, pindex);
}

// 检测是不是完全平方数
int full_sqrt(int n) {
        int s = (int)sqrt(n);
        return s * s == n;
}

int satisfy(int n, int *primes) {
        for (int i = 0; i < LIMIT; i++) {
                if (primes[i] > n)
                        return 0;
                if (full_sqrt((n - primes[i]) / 2)) {
                        return 1;
                }
        }
        return 0;
}

int main() {
        clock_t begin = clock();
        int pindex = 0;
        int primes[LIMIT] = {0};
        find_primes(primes, 0, pindex);
        int res = 0;
        int first_unsatisfy = 3;
        while (1) {
                if (probablyPrime(first_unsatisfy, 3)) {
                        // 素数pass
                        first_unsatisfy += 2; // 奇数
                        continue;
                }
                if (!satisfy(first_unsatisfy, primes)) {
                        /* printf("%d\n", first_unsatisfy); */
                        res = first_unsatisfy;
                        break;
                }

                first_unsatisfy += 2;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", res, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
