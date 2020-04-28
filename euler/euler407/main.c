/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define DEBUG */

// find largest prime factor of each number up to "limit"
uint32_t *findLargestPrimes(uint32_t limit) {
        uint32_t *vec = (uint32_t *)calloc(limit + 1, sizeof(uint32_t));

        for (uint32_t i = 2; i < limit; i++) {
                // skip if i is not a prime
                if (vec[i] > 0)
                        continue;

                // modify all multiples
                for (uint32_t j = i; j <= limit; j += i) {
                        vec[j] = i;
                }

                // and all exponents i^2, i^3, i^4 ...
                uint32_t j = i * i;
                while (j <= limit) {
                        vec[j] = j;
                        j *= i;
                }
        }

        return vec;
}

// this program's aim is to find largest a<n where a(a-1) is a multiple of n.
// Each prime factor of n has to be either a prime factor of a or a-1
// if n has only one prime factor -> a = 1
uint32_t search(uint32_t n, uint32_t *largestPrimes) {
        if (n == 1) {
                return 0;
        }

        // always return 1 if n has only one prime factor
        uint32_t p = largestPrimes[n];
        if (p == n) {
                return 1;
        }

        // start from largest multiples os n's largest prime factor
        uint32_t start = n - n % p;
        for (uint64_t x = start; x >= p; x -= p) {

                // check a-1
                uint64_t next = x + 1;
                if ((next * next) % n == next) {
                        return (uint32_t)next;
                }

                // check a
                if ((x * x) % n == x) {
                        return (uint32_t)x;
                }
        }
        return 1;
}

int main() {
        uint32_t limit = 10000000;
        uint32_t *vec = findLargestPrimes(limit);
        uint64_t sum = 0;

        for (uint32_t n = 1; n <= limit; n++) {
                uint32_t tmp = search(n, vec);
#ifdef DEBUG
                printf("M(%d) = %d\n", n, tmp);
#endif
                sum += (uint64_t)tmp;
        }

        free(vec);
        printf("%lu\n", sum);
        return 0;
}
