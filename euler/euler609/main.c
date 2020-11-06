/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-05
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

#define IS_PRIME(a) (is_in_sieve((a)))

const uint32_t MAX = 1e5;
const uint32_t MOD = 1e9 + 7;
static char SIEVE[MAX / 16 + 1];
static uint32_t PRIMES[10000000];
static uint32_t PRIMES_SIZE = 0;

static inline bool is_in_sieve(long idx) { return !(SIEVE[idx / 16] & (1 << (idx % 16 / 2))); }
static inline void remove_from_sieve(long idx) { SIEVE[idx / 16] |= (1 << (idx % 16 / 2)); }

void primeSieve() {
        memset(SIEVE, 256, MAX / 16 + 1);
        long i, j;
        for (i = 3; i * i <= MAX; i += 2) {
                if (IS_PRIME(i)) {
                        for (j = i * i; j <= MAX; j += 2 * i) {
                                remove_from_sieve(j);
                        }
                }
        }
        PRIMES[PRIMES_SIZE++] = 2;

        for (int i = 3; i < MAX; i += 2) {
                if (IS_PRIME(i)) {
                        PRIMES[PRIMES_SIZE++] = i;
                }
        }
        printf("%d\n", PRIMES_SIZE);
}

int main() {
        primeSieve();
        printf("sieve finished\n");
        int pi[MAX + 1] = {0};
        int p[100] = {0};
        for (int i = 0; i < PRIMES_SIZE; i++) {
                pi[PRIMES[i]] = 1;
        }
        for (int i = 1; i < MAX; i++) {
                pi[i] += pi[i - 1];
                for (int w = i, cnt = 0; w > 0; w = pi[w]) {
                        if (pi[w] == pi[w - 1]) { // 非素数
                                ++cnt;
                        }
                        if (w != i) {
                                p[cnt] += 1;
                        }
                }
        }
        uint64_t ans = 1;
        for (int i = 0; i <= 100; ++i) {
                if (p[i] == 0) {
                        break;
                }
                ans = ans * (p[i] % MOD) % MOD;
        }
        printf("%lu\n", ans);
        return 0;
}
