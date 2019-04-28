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

void fillPrimes(uint64_t size, array *vec) {
        kv_resize(int, *vec, size);

        vec->a[0] = 1;
        vec->a[1] = 1;
        for (uint64_t i = 2; i < size; i++)
                vec->a[i] = 0;

        // find primes in [0, sqrt(size))
        for (uint64_t i = 2; i * i < size; i++) {

                for (uint64_t j = 2; j * j <= i; j++) {
                        if (i % j == 0) {
                                vec->a[i] = 1;
                                break;
                        }
                }
                if (vec->a[i] == 0) {
                        // mark multiples as non-prime
                        for (uint64_t k = i << 1; k < size; k += i)
                                vec->a[k] = 1;
                }
        }
}

// 筛出[a, b)中的素数
void segment_sieve(uint64_t a, uint64_t b, array *vec) {
        array small_vec;
        kv_init(small_vec);
        kv_resize(int, *vec, b - a);

        for (uint64_t i = 0; i < b - a; i++)
                vec->a[i] = 0;

        uint64_t sb = 1;
        for (; sb * sb < b; sb++)
                ;
        sb--;
        fillPrimes(sb, &small_vec); // find primes in [0 sqrt(b))

        for (uint64_t i = 0; i < sb; i++) {
                if (small_vec.a[i] == 0) {
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
        /*         if (vec.a[i] == 0) */
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
