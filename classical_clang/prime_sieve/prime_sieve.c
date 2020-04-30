/*
 * =====================================================================================
 *
 *       Filename:  prime_sieve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100L

char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(long idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

bool isPrime(int x) { return is_in_sieve(x); }

void primeSieve() {
        memset(sieve, 256, MAX / 16 + 1);
        long i, j;
        for (i = 3; i * i <= MAX; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
}

int main() {
        primeSieve();
        printf("2 ");
        for (int i = 3; i < MAX; i += 2) {
                if (isPrime(i)) {
                        printf("%d ", i);
                } else {
		  // printf("(%d) ", i);
                }
        }
        printf("\n");
        return 0;
}
