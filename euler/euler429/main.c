/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MAX 100000000L
#define MODULE 1000000009L

char sieve[MAX / 16 + 1];

static inline bool is_in_sieve(long idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

bool isPrime(int x) {
        if (x == 2) {
                return true;
        }
        return is_in_sieve(x);
}

void primeSieve() {
        memset(sieve, 256, MAX / 16 + 1);
        long i, j;
        for (i = 3; i * i <= MAX; i += 2) {
                if (is_in_sieve(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
}

// 计算 m^n % k
uint32_t powMod(uint32_t m, uint32_t n, uint32_t k) {
        if (n == 1)
                return m % k;
        if (n == 2) {
                return (uint32_t)((uint64_t)m * m % k);
        }

        if (m % k == 0)
                return 0;

        uint32_t b = powMod(m, 2, k);
        if (n % 2 == 0) {
                return powMod(b, n >> 1, k);
        } else {
                return (uint32_t)((uint64_t)m * powMod(b, (n - 1) >> 1, k) % k);
        }
}

int main() {
        uint64_t ans = 1;
        primeSieve();
        for (uint32_t p = 2; p <= MAX; p += 2) {
                if (!isPrime(p))
                        continue;

                // count = {max(x) for p^x | MAX!}
                // https://en.wikipedia.org/wiki/Legendre%27s_formula
                uint64_t pw = (uint64_t)p;
                uint32_t count = 0;
                while (pw <= MAX) {
                        if (pw * 2 > MAX) {
                                count++;
                                break;
                        }

                        count += (uint32_t)(MAX / pw);
                        pw *= p;
                }

                // printf("p -> %d, count -> %d\n", p, count);
                ans *= (1 + powMod(p, 2 * count, MODULE));
                ans %= MODULE;
                if (p == 2) {
                        p--;
                }
        }
        printf("%lu\n", ans);

        return 0;
}
