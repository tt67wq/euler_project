/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-05
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100L
#define IS_PRIME(a) (is_in_sieve((a)))

static char SIEVE[MAX / 16 + 1];
static uint32_t PRIMES[10000];
static uint32_t PRIME_SIZE = 0;

static inline bool is_in_sieve(long idx) { return !(SIEVE[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { SIEVE[idx / 16] |= (1 << (idx % 16 / 2)); }

void primeSieve() {
        memset(SIEVE, 256, MAX / 16 + 1);
        long i, j;
        for (i = 3; i * i <= MAX; i += 2) {
                if (IS_PRIME(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
}

int main() {
        primeSieve();
        PRIMES[PRIME_SIZE++] = 2;

        for (int i = 3; i < MAX; i += 2) {
                if (IS_PRIME(i)) {
                        PRIMES[PRIME_SIZE++] = i;
                } else {
                        // printf("(%d) ", i);
                }
        }
        for (int i = 0; i < PRIME_SIZE; i++) {
                printf("%d ", PRIMES[i]);
        }
        printf("\n");
        return 0;
}
