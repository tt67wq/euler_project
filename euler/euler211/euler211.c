/*
 * =====================================================================================
 *
 *       Filename:  euler211.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-06-18
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
#define N 64000000LL
/* #define N 100LL */

typedef long long ll;
typedef kvec_t(ll) array;

void pre(array *vec) {
        for (ll i = 2; i <= N; i++) {
                vec->a[i] = 1 + i * i;
        }

        vec->a[1] = 1;
}

void iter(array *vec) {
        for (ll i = 2; i * 2 <= N; i++) {
                /* ll k = vec->a[i]; */
                for (ll j = i * 2; j <= N; j += i)
                        vec->a[j] += i * i;
        }
}

int is_perfect(ll n) {
        ll sq = sqrt(n);
        if (sq * sq == n)
                return 1;
        return 0;
}

int main(int argc, const char *argv[]) {
        array sieve;
        kv_init(sieve);
        kv_resize(ll, sieve, N);

        pre(&sieve);
        iter(&sieve);

        ll s = 0;

        for (ll i = 1; i <= N; i++) {
                /* printf("%llu => %llu\n", i, sieve.a[i]); */
                if (is_perfect(sieve.a[i]))
                        s += i;
        }
        printf("%llu\n", s);
        return 0;
}
