/*
 * =====================================================================================
 *
 *       Filename:  euler187.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef kvec_t(uint64_t) array;

int isNotPrime(uint64_t x, array *vec) {
        if ((x & 1) == 0)
                return !(x == 2);
        return vec->a[x >> 1];
}

void fillPrimes(uint64_t size, array *vec) {
        uint64_t half = (size >> 1) + 1;
        kv_resize(uint64_t, *vec, half);

        // 1 is not prime
        vec->a[0] = 1;

        // 筛法
        for (uint64_t i = 1; 2 * i * i < half; i++) {
                if (!(vec->a[i])) {
                        // mark all its multiples as false
                        uint64_t current = 3 * i + 1;
                        while (current < half) {
                                vec->a[current] = 1;
                                current += 2 * i + 1;
                        }
                }
        }
}

int main() {
        double dtime = clock();
        uint64_t counter = 0;
        array vec;
        array primes;
        kv_init(vec);
        kv_init(primes);

        // gen all primes before 5*10e7
        fillPrimes(50000000, &vec);
        for (uint64_t i = 0; i < 50000000; i++) {
                if (!isNotPrime(i, &vec)) {
                        kv_push(uint64_t, primes, i);
                }
        }

        for (uint64_t i = 0; i < kv_size(primes); i++) {
                for (uint64_t j = i; j < kv_size(primes); j++) {
                        if (kv_A(primes, j) * kv_A(primes, i) <= 100000000) {
                                counter++;
                        } else {
                                break;
                        }
                }
        }

        printf("%llu\n", counter);
        dtime = (double)(clock() - dtime) / CLOCKS_PER_SEC;
        printf("time=%.3lf sec.\n", dtime);

        return 0;
}
