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

ull PHI_SIEVE[MAX + 1] = {0};

static inline int is_in_sieve(char *sieve, ull idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
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

void pre() {
        for (ull i = 1; i <= MAX; i++)
                PHI_SIEVE[i] = i;
        return;
}

char is_prime(ull n) {
        for (ull i = 2; i * i <= n; i++) {
                if (n % i == 0)
                        return 0;
        }
        return 1;
}

void phi_sieve() {
        ull i = 2;
        for (; i * i <= MAX; i++) {
                if (is_prime(i)) {
                        for (ull j = i; j <= MAX; j += i) {
                                PHI_SIEVE[j] -= PHI_SIEVE[j] / i;
                        }
                }
        }
        for (; i <= MAX; i++) {
                if (PHI_SIEVE[i] == i) {
                        // prime
                        for (ull j = i; j <= MAX; j += i) {
                                PHI_SIEVE[j] -= PHI_SIEVE[j] / i;
                        }
                }
        }
}

ull phi(ull n, array *primes) {
        for (int i = 0;; i++) {
                ull p = kv_A(*primes, i);
                if (p > n)
                        break;
                if (n % p == 0)
                        n -= n / p;
        }
        return n;
}

int chain_len(ull n) {
        if (n == 1)
                return 1;
        if (n == 2)
                return 2;

        int res = 1;
        int over = 0;
        int cn = n;
        while (cn > 1) {
                cn = PHI_SIEVE[cn];

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

void print_phi_chain(ull n, array *primes) {
        while (n > 1) {
                printf("%ld => ", n);
                /* n = SIEVE[n]; */
                n = phi(n, primes);
        }
        printf("1\n");
}

int main(int argc, const char *argv[]) {
        array primes;
        kv_init(primes);

        prime_sieve(MAX, &primes);
        pre();
        phi_sieve();

        ull sum = 0;

        for (int j = 0; j < kv_size(primes); j++) {
                ull p = kv_A(primes, j);
                int l = chain_len(p - 1);
                if (l == 24) {
                        sum += p;
                        if (sum < 1677366278943ll)
                                printf("chain_len of %lu = %d, now sum is %lu\n", p - 1, l, sum);
                }
        }
        printf("%lu\n", sum);

        /* ull m; */

        /* while (1) { */
        /*         printf("Enter a number: "); */
        /*         scanf("%ld", &m); */
        /*         print_phi_chain(m, &primes); */
        /* } */

        return EXIT_SUCCESS;
}
