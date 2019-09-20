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

#define MAX 1000L

char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(long idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
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
        long i;
        init();
        prime_sieve();
        printf("2 ");
        for (i = 3; i < MAX; i += 2) {
                if (is_in_sieve(i)) {
                        printf("%ld ", i);
                } else {
                        printf("(%ld) ", i);
                }
        }
        printf("\n");
        return 0;
}
