/*
 * =====================================================================================
 *
 *       Filename:  gen_prime.c
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

typedef kvec_t(int) array;

int isNotPrime(uint64_t x, array *vec) {
        if ((x & 1) == 0)
                return !(x == 2);
        return vec->a[x >> 1];
}

void fillPrimes(uint64_t size, array *vec) {
        uint64_t half = (size >> 1) + 1;
        kv_resize(int, *vec, half);

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

// 筛出[a, b)中的素数
void segment_sieve(uint64_t a, uint64_t b, array *vec) {
        array small_vec;
        kv_init(small_vec);
        kv_resize(int, *vec, b - a);

        uint64_t sb = 1;
        for (; sb * sb < b; sb++)
                ;
        sb--;
        fillPrimes(sb, &small_vec); // find primes in [0 sqrt(b))

        for (uint64_t i = 0; i < sb; i++) {
                if (!isNotPrime(i, &small_vec)) {
                        // filter all multiples of i
                        for (uint64_t k = i; k < b; k += i) {
                                if (k < a)
                                        continue;
                                vec->a[k - a] = 1;
                        }
                }
        }
}

int main() {
        array vec;
        kv_init(vec);

        /* fillPrimes(300, &vec); */
        /* for (int i = 0; i < 300; i++) { */
        /*         if (!isNotPrime(i, &vec)) */
        /*                 printf("%d ", i); */
        /* } */
        /* printf("\n"); */

        segment_sieve(10000, 10050, &vec);
        for (int i = 0; i < 50; i++) {
                if (vec.a[i] == 0)
                        printf("%d ", i + 10000);
        }

        return 0;
}
