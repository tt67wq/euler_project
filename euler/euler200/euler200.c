/*
 * =====================================================================================
 *
 *       Filename:  euler200.c
 *
 *    Description:  欧拉计划200题
 *
 *        Version:  1.0
 *        Created:  2019-05-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

// 由于素数校验算法凉了，所以这题暂时有点问题

#include "kvec.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIGLIM (1ull << 38)
typedef kvec_t(int) array;
typedef kvec_t(uint64_t) big_array;

//////////// prime tools //////////////
static inline bool is_in_sieve(char *sieve, uint64_t idx) {
        return !(sieve[idx / 16] & (1 << (idx % 16 / 2)));
}
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, uint64_t idx) {
        sieve[idx / 16] |= (1 << (idx % 16 / 2));
}

void prime_sieve(uint64_t max, big_array *primes) {
        char *sieve = calloc(max / 16 + 1, 1);
        uint64_t max_sqrt = sqrt(max);
        for (uint64_t i = 3; i <= max_sqrt; i += 2) {
                if (is_in_sieve(sieve, i)) {
                        for (uint64_t j = i * i; j <= max; j += 2 * i) {
                                remove_from_sieve(sieve, j);
                        }
                }
        }

        kv_push(uint64_t, *primes, 2);
        for (uint64_t i = 3; i <= max; i += 2) {
                if (is_in_sieve(sieve, i))
                        kv_push(uint64_t, *primes, i);
        }

        free(sieve);
}

static int isprime(uint64_t x) {
        uint64_t i;
        if (x % 2 == 0)
                return 0;
        for (i = 3; i * i <= x; i++)
                if (x % i == 0)
                        return 0;
        return 1;
}

//////////// prime tools //////////////

void num2digits(uint64_t num, array *digits) {
        while (num) {
                kv_push(int, *digits, num % 10);
                num /= 10;
        }
}

uint64_t digits2num(array *digits) {
        uint64_t num = 0;
        for (int i = kv_size(*digits) - 1; i >= 0; i--)
                num = num * 10 + kv_A(*digits, i);

        return num;
}

static int ispp(uint64_t x) {
        uint64_t digit[21], scale[21], xtmp;
        int i, j, top;
        for (i = scale[0] = 1; i < 21; i++)
                scale[i] = 10 * scale[i - 1];
        for (top = -1, xtmp = x; xtmp; xtmp /= 10) {
                digit[++top] = xtmp % 10;
        }
        for (i = 0; i < top; i++)
                for (j = 0; j < 10; j++)
                        if (j != digit[i]) {
                                if (isprime(x + scale[i] * (j - digit[i]))) {
                                        return 0;
                                }
                        }
        return 1;
}

char *num2str(uint64_t num) {
        array digits;
        kv_init(digits);
        num2digits(num, &digits);

        char *str = calloc(kv_size(digits), sizeof(char));
        int j = 0;
        for (int i = kv_size(digits) - 1; i >= 0; i--) {
                str[j] = kv_A(digits, i) + '0';
                j++;
        }
        kv_destroy(digits);
        return str;
}

int contains200(uint64_t sq) {
        int t = 0;
        while (sq) {
                int r = sq % 10;
                if (t < 2) {
                        if (r == 0)
                                t++;
                        else
                                t = 0;
                } else if (t == 2) {
                        if (r == 2)
                                t = 3;
                        else if (r)
                                t = 0;
                }
                sq /= 10;
        }
        return t >= 3;
}

int cmp(const void *a, const void *b) {
        const uint64_t *p = a;
        const uint64_t *q = b;
        return *p > *q ? 1 : -1;
}

int main(int argc, const char *argv[]) {

        big_array primes;
        kv_init(primes);

        big_array res;
        kv_init(res);

        prime_sieve(200000, &primes);
        for (int i = 0; i < kv_size(primes); i++) {
                for (int j = 0; j < kv_size(primes); j++) {
                        if (j == i)
                                continue;

                        uint64_t p = kv_A(primes, i);
                        uint64_t q = kv_A(primes, j);
                        uint64_t r = p * p * q * q * q;
                        if (r > BIGLIM)
                                continue;

                        if (!contains200(r))
                                continue;
                        if (!ispp(r))
                                continue;

                        kv_push(uint64_t, res, r);
                }
        }

        // sort
        qsort(res.a, (int)kv_size(res), sizeof(res.a[0]), cmp);

        for (int i = 0; i < kv_size(res); i++) {
                printf("%d, %llu\n", i, kv_A(res, i));
                if (i > 300)
                        break;
        }

        return 0;
}
