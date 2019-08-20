/*
 * =====================================================================================
 *
 *       Filename:  euler_357.c
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

#define MAX (unsigned long long)1e8

typedef unsigned long long uint64_t;
char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }
static inline bool is_prime(uint64_t idx) { return is_in_sieve(idx) && idx % 2 == 1; }

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
        uint64_t i, j, max_sqrt;
        max_sqrt = sqrt(MAX);
        for (i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
}

bool filter(uint64_t n) {
        uint64_t i;
        bool flag = true;
        for (i = 3; i * i <= n; i++) {
                if (n % i == 0) {
                        if (!is_prime(n / i + i)) {
                                flag = false;
                                break;
                        }
                }
        }
        return flag;
}

int main() {
        uint64_t i, s = 0;
        init();
        prime_sieve();
        for (i = 2; i < MAX; i += 4) {
                if (!is_prime(i + 1))
                        continue;
                if (!is_prime((i >> 1) + 2))
                        continue;
                if (!filter(i))
                        continue;
                /* printf("%llu ", i); */
                s += i;
        }
        printf("%llu\n", s + 1);
        return 0;
}
