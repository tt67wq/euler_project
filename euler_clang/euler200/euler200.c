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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef kvec_t(int) array;
typedef kvec_t(uint64_t) big_array;

//////////// prime tools //////////////
static inline bool is_in_sieve(char *sieve, uint64_t idx) { return !(sieve[idx / 16] & (1 << (idx % 16 / 2))); }
/* remove the odd number idx from the sieve */
static inline void remove_from_sieve(char *sieve, uint64_t idx) { sieve[idx / 16] |= (1 << (idx % 16 / 2)); }

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

int isPrime(uint64_t n) {
        if (n == 1)
                return 0;
        for (int i = 2; i * i <= n; i++) {
                if (n % i == 0)
                        return 0;
        }
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

void replace_at(array *digits, int index, int target) { digits->a[index] = target; }

int no_prime_in_cluster(uint64_t num) {
        array digits;
        kv_init(digits);
        num2digits(num, &digits);

        if (num % 2 == 0) {
                // only check last one
                for (int j = 1; j < 10; j += 2) {
                        replace_at(&digits, 0, j);
                        printf("%llu\n", digits2num(&digits));
                        if (probablyPrime(digits2num(&digits), 3))
                                return 0;
                }
        } else {
                for (int i = 0; i < kv_size(digits); i++) {
                        int origin = kv_A(digits, i);
                        if (i) {
                                for (int j = 1; j < 10; j += 2) {
                                        if (j == origin)
                                                continue;
                                        replace_at(&digits, i, j);
                                        if (probablyPrime(digits2num(&digits), 3))
                                                return 0;
                                }
                        } else {
                                for (int j = 0; j < 10; j++) {
                                        if (j == origin)
                                                continue;
                                        replace_at(&digits, i, j);
                                        if (probablyPrime(digits2num(&digits), 3))
                                                return 0;
                                }
                        }
                        replace_at(&digits, i, origin);
                }
        }
        kv_destroy(digits);
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

int contains200(uint64_t num) {

        char *str = num2str(num);
        char *substr = "200";
        if (strstr(str, substr))
                return 1;
        return 0;
}

int cmp(const void *a, const void *b) {
        const uint64_t *p = a;
        const uint64_t *q = b;
        /* printf("%llu, %llu, %d\n", *p, *q, *p > *q); */
        return *p > *q ? 1 : -1;
}

int main(int argc, const char *argv[]) {

        big_array primes;
        kv_init(primes);

        big_array res;
        kv_init(res);

        prime_sieve(200000, &primes);
        for (int i = 0; i < 3; i++) {
                for (int j = 3; j < kv_size(primes); j++) {
                        /* if (j == i) */
                        /*         continue; */
                        uint64_t q = kv_A(primes, i);
                        uint64_t p = kv_A(primes, j);
                        uint64_t r = p * p * q * q * q;
                        if (no_prime_in_cluster(r) && contains200(r))
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
