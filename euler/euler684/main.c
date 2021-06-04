/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-02
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

// https://projecteuler.net/problem=684

void fibnacci(intmax_t *fib) {
        fib[0] = 0;
        fib[1] = 1;
        int i = 2;
        while (i <= 90) {
                fib[i] = fib[i - 1] + fib[i - 2];
                i++;
        }
}

intmax_t pow_modulo(int a, intmax_t b, int n) {
        intmax_t x = 1, y = a;
        while (b > 0) {
                if (b % 2 == 1) {
                        x = (x * y) % n; // multiplying with base
                }
                y = (y * y) % n; // squaring the base
                b /= 2;
        }
        return x % n;
}

intmax_t S(intmax_t k) {

        int r = k % 9;

        return (pow_modulo(10, floor(k / 9), MOD) * ((r * r + 3 * r + 12) >> 1) - 6 - k) % MOD;
}

int main() {

        intmax_t *fib = (intmax_t *)calloc(91, sizeof(intmax_t));
        fibnacci(fib);

        intmax_t ans = 0;
        for (int i = 2; i <= 90; i++) {
                intmax_t k = fib[i];
                intmax_t _t = S(k);
                ans += _t;
                printf("%ld, %ld\n", k, _t);
                ans %= MOD;
        }
        puts("");
        printf("%lu\n", ans);

        return 0;
}