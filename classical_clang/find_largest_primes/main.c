/*
 * =====================================================================================
 *
 *       Filename:  find_largest_primes.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-29
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

#define DEBUG

void findLargestPrimes(uint32_t limit, uint32_t **vec) {

        for (uint32_t i = 2; i < limit; i++) {
                // skip if i is not a prime
                if ((*vec)[i] > 0)
                        continue;

                // modify all multiples
                for (uint32_t j = i; j <= limit; j += i) {
                        (*vec)[j] = i;
                }

                // and all exponents i^2, i^3, i^4 ...
                uint64_t j = (uint64_t)i * i;
                while (j <= limit) {
                        (*vec)[j] = (uint32_t)j;
                        j *= i;
                }
        }
}

int main() {
        int limit = 100;
        uint32_t *vec = (uint32_t *)calloc(limit + 1, sizeof(uint32_t));
        findLargestPrimes((uint32_t)limit, &vec);
        for (int i = 0; i < limit; i++) {
                printf("largestPrime[%d] = %d\n", i, vec[i]);
        }
        free(vec);
        return 0;
}
