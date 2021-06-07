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

intmax_t pow_modulo(int a, intmax_t b, const int n) {
        intmax_t x = 1, y = a;
        while (b > 0) {
                if (b & 1) {
                        x = (x * y) % n; // multiplying with base
                }
                y = (y * y) % n; // squaring the base
                b = b >> 1;
        }
        return x % n;
}

intmax_t divFloor(intmax_t a, int b) {
        intmax_t _t = a / b;
        if (_t * b > a) {
                return _t - 1;
        }
        return _t;
}

intmax_t S(const intmax_t k) {

        int r = k % 9;
        intmax_t p1 = pow_modulo(10, divFloor(k, 9), MOD);
        int p2 = (r * r + 3 * r + 12) >> 1;

        // printf("%ld, %d\n", p1, p2);

        intmax_t _tmp = p1 * p2 - 6 - k;

        _tmp %= MOD;
        if (_tmp < 0) {
                return MOD + _tmp;
        }
        return _tmp;
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