/*
 * =====================================================================================
 *
 *       Filename:  factorial.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-17
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

#define MAX 100000000L

typedef unsigned long long uint64_t;

char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

void init() { memset(sieve, 256, MAX / 16 + 1); }
void prime_sieve() {
        uint64_t i, j, max_sqrt;
        max_sqrt = sqrt(MAX);
        for (i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i)
                                remove_from_sieve(j);
                }
        }
}

long extend_gcd(long a, long b) {
        long a1 = 0;
        long a2 = 1;

        long b1 = 1;
        long b2 = 0;

        long tmp, c;

        while (b != 0) {
                c = a / b;
                tmp = a;
                a = b;
                b = tmp % b;

                tmp = a1;
                a1 = a2 - c * a1;
                a2 = tmp;

                tmp = b1;
                b1 = b2 - c * b1;
                b2 = tmp;
        }
        return a2;
}

long niyuan(long a, long b) {
        long g = extend_gcd(a, b);
        return g > 0 ? g : b + g;
}

long factorial_mod(long n, long p) {
        long res = 1;
        while (n > 1) {
                res *= n;
                if (res >= p)
                        res %= p;
                if (res == 0)
                        break;
                n--;
        }
        return res;
}

long S2(long p) {
        int i;
        long t, s = (p - 1) / 2;
        for (i = 4; i < 6; i++) {
                t = factorial_mod(p - i, p);
                s += t;
                if (s >= p)
                        s %= p;
        }
        return s;
}

long S(long p) {
        long t, s;
        s = (p - 1) / 2;
        t = (niyuan(p - 3, p) * s) % p;
        s += t;
        s += (niyuan(p - 4, p) * t) % p;
        return s % p;
}

int main() {
        long i, c = 1;
        long s = 0;
        init();
        prime_sieve();
        for (i = 5; i < MAX; i += 2) {
                if (is_in_sieve((uint64_t)i)) {
			printf("%ld ", c);
                        s += S(i);
                        c += 1;
                }
        }
        printf("%ld\n", s);
        return 0;
}
