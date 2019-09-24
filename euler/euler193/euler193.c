/*
 * =====================================================================================
 *
 *       Filename:  euler193.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-22
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

// mark non-squarefree nums
void fill_squarefree(uint64_t limit, array *vec, array *primes) {
        kv_resize(int, *vec, limit);

        for (uint64_t i = 0; i * i < limit; i++) {

                if (!isNotPrime(i, primes)) {
                        for (uint64_t j = i * i; j < limit; j += i * i)
                                vec->a[j] = 1;
                }
        }
        return;
}

void count_factors(uint64_t limit, array *fn) {
        kv_resize(int, *fn, limit);
        for (uint64_t i = 2; i < limit; i++) {
                if (kv_A(*fn, i))
                        continue;
                for (uint64_t j = i; j < limit; j += i) {
                        fn->a[j]++;
                }
        }
}

int main(int argc, const char *argv[]) {
        array primes;
        array vec;
        array fn;
        kv_init(primes);
        kv_init(vec);
        kv_init(fn);

        uint64_t sum = 0;
        uint64_t limit = 1ULL << 50;
        uint64_t root = 1 << 25;
        printf("%llu\n", root);

        fillPrimes(1 << 13, &primes);

        fill_squarefree(root, &vec, &primes);
        count_factors(root, &fn);

        // count non-squarefree nums
        for (uint64_t i = 2; i * i < limit; i++) {
                if (kv_A(vec, i) == 0) {
                        // squarefree num
                        if (kv_A(fn, i) % 2 == 1)
                                sum += limit / (i * i);
                        else
                                sum -= limit / (i * i);
                }
        }

        printf("%llu\n", limit - sum);
        return 0;
}
