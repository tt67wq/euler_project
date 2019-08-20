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

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20LL

typedef unsigned long long uint64_t;
char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void f(int n) {
        if (n)
                f(n / 2);
        else
                return;
        printf("%d", n % 2);
}

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
        uint64_t i, j, max_sqrt;
        max_sqrt = sqrt(MAX);
        for (i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(i)) {
                        printf("%lld is in sieve\n", i);
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                printf("removing %lld\n", j);
                                remove_from_sieve(j);
                        }
                }
        }
}

int main() {
        int i;
        init();

        prime_sieve();
        printf("2 ");
        for (i = 3; i < MAX; i += 2) {
                if (is_in_sieve((uint64_t)i)) {
                        printf("%d ", i);
                } else {
                        printf("(%d) ", i);
                }
        }
        printf("\n");
        return 0;
}
