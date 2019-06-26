/*
 * =====================================================================================
 *
 *       Filename:  euler214.c
 *
 *    Description:  欧拉计划214题
 *
 *        Version:  1.0
 *        Created:  2019-06-26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 40000000LL
#define SQ 6325

typedef unsigned long ull;
typedef kvec_t(int) array;
typedef kvec_t(ull) big_array;

int CACHE[MAX] = {0};

//////////// prime tools
static inline int is_in_sieve(char *sieve, ull idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, ull idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void prime_sieve(ull max, big_array *primes) {
        char *sieve = calloc(max / 16 + 1, 1);
        ull max_sqrt = sqrt(max);
        for (ull i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(sieve, i)) {
                        for (ull j = i * i; j <= max; j += 2 * i) {
                                remove_from_sieve(sieve, j);
                        }
                }
        }

        kv_push(ull, *primes, 2);
        for (ull i = 3; i <= max; i += 2) {
                if (is_in_sieve(sieve, i))
                        kv_push(ull, *primes, i);
        }

        free(sieve);
}

ull gcd(ull m, ull n) {
        ull r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

ull euler(ull n) {
        if (n == 2)
                return 1;
        ull res = 0;
        for (ull i = 2; i < n; i++) {
                if (gcd(i, n) == 1)
                        res++;
        }
        return res + 1;
}

int chain_len(ull n) {
        if (n == 1)
                return 1;
        if (n == 2)
                return 2;
        if (CACHE[n] != 0)
                return CACHE[n];
        int res = 1 + chain_len(euler(n));
        CACHE[n] = res;
        return res;
}

int main(int argc, const char *argv[]) {
        big_array primes;
        kv_init(primes);

        ull sum = 0;

        prime_sieve(MAX, &primes);
        for (int j = 0; j < kv_size(primes); j++) {
                if (chain_len(kv_A(primes, j) - 1) == 24) {
                        sum += kv_A(primes, j);
                }
        }
        printf("%lu\n", sum);

        return EXIT_SUCCESS;
}
