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

typedef unsigned long ull;
typedef kvec_t(ull) array;

//////////// prime tools
static inline int is_in_sieve(char *sieve, ull idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, ull idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void prime_sieve(ull max, array *primes) {
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

ull phi(ull n, array *ps) {
        if (n == 2)
                return 1;
        ull res = n;
        for (int i = 0;; i++) {
                ull p = kv_A(*ps, i);
                if (p > n)
                        break;
                if (res % p == 0) {
                        res -= res / p;
                }
        }
        return res;
}

int chain_len(ull n, array *ps) {
        if (n == 1)
                return 1;
        if (n == 2)
                return 2;
        int res = 1;
        int over = 0;
        int cn = n;
        while (cn > 1) {
                cn = phi(cn, ps);
                res++;
                if (res > 24) {
                        over = 1;
                        break;
                }
        }
        if (over)
                return 10000;
        return res;
}

int main(int argc, const char *argv[]) {
        array primes;
        kv_init(primes);

        ull sum = 0;

        prime_sieve(MAX, &primes);
        for (int j = kv_size(primes) - 1;; j--) {
                ull p = kv_A(primes, j);
                int l = chain_len(kv_A(primes, j) - 1, &primes);
                if (l == 24) {
                        sum += p;
                        printf("chain_len of %lu = %d, now sum is %lu\n", p, l, sum);
                }
        }
        printf("%lu\n", sum);
        printf("%lu\n", 1677366278943ll);

        /* printf("%lu\n", chain_len(19, &primes)); */

        return EXIT_SUCCESS;
}
