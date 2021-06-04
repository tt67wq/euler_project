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

void fibnacci(uint64_t *fib) {
        fib[0] = 0;
        fib[1] = 1;
        int i = 2;
        while (i <= 90) {
                fib[i] = fib[i - 1] + fib[i - 2];
                i++;
        }
}

uint64_t pow_mod(uint64_t m, uint64_t n, uint64_t k) {
        if (n == 0) {
                return 1;
        }
        if (n == 1)
                return m % k;
        if (n == 2)
                return (m * m) % k;

        if (m % k == 0)
                return 0;

        uint64_t b = pow_mod(m, 2, k);
        if (n & 1) {
                return pow_mod(b, n / 2, k);
        } else {
                return (m * pow_mod(b, (n - 1) / 2, k)) % k;
        }
}

uint64_t getS(uint64_t k) {
        uint64_t n = (uint64_t)floor(k / 9);
        int r = n % 9 + 2;

        return (((r - 1) * r + 10) * pow_mod(10, n, MOD) - (r + 9 * n + 4)) % MOD;
}

int main() {

        uint64_t *fib = (uint64_t *)calloc(91, sizeof(uint64_t));
        fibnacci(fib);

        uint64_t ans = 0;
        for (int i = 2; i <= 90; i++) {
                uint64_t k = fib[i];
                ans += getS(k);
                printf("%lu\n", k);
                ans %= MOD;
        }
        puts("");
        printf("%lu\n", ans);

        return 0;
}