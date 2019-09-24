/*
 * =====================================================================================
 *
 *       Filename:  euler196.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef kvec_t(int) array;

void fillPrimes(uint64_t size, array *vec) {
        kv_resize(int, *vec, size);

        vec->a[0] = 1;
        vec->a[1] = 1;
        for (uint64_t i = 2; i < size; i++)
                vec->a[i] = 0;

        // find primes in [0, sqrt(size))
        for (uint64_t i = 2; i * i < size; i++) {

                for (uint64_t j = 2; j * j <= i; j++) {
                        if (i % j == 0) {
                                vec->a[i] = 1;
                                break;
                        }
                }
                if (vec->a[i] == 0) {
                        // mark multiples as non-prime
                        for (uint64_t k = i << 1; k < size; k += i)
                                vec->a[k] = 1;
                }
        }
}

// 筛出[a, b)中的素数
void segment_sieve(uint64_t a, uint64_t b, array *vec) {
        array small_vec;
        kv_init(small_vec);
        kv_resize(int, *vec, b - a);

        for (uint64_t i = 0; i < b - a; i++)
                vec->a[i] = 0;

        uint64_t sb = 1;
        for (; sb * sb < b; sb++)
                ;
        sb--;
        fillPrimes(sb, &small_vec); // find primes in [0 sqrt(b))
        printf("find primes in [0 %llu) finished\n", sb);

        for (uint64_t i = 0; i < sb; i++) {
                if (small_vec.a[i] == 0) {
                        // filter all multiples of i
                        for (uint64_t k = (uint64_t)(a / i) * i; k < b; k += i) {
                                if (k < a)
                                        continue;
                                vec->a[k - a] = 1;
                        }
                }
        }
        kv_destroy(small_vec);
}

uint64_t get_number(uint64_t level, uint64_t row) { return (level * (level - 1) >> 1) + row; }

void get_around(uint64_t level, uint64_t row, uint64_t *group) {
        group[4] = get_number(level, row);
        if (row == 1) {
                group[0] = 0;
                group[3] = 0;
                group[6] = 0;

                group[1] = get_number(level - 1, row);
                group[2] = group[1] + 1;
                group[5] = group[4] + 1;
                group[7] = group[6] + 1;
                group[8] = group[7] + 1;
                return;
        }
        group[0] = get_number(level - 1, row - 1);
        group[1] = group[0] + 1;
        group[2] = group[1] + 1;
        group[3] = get_number(level, row) - 1;
        group[5] = group[4] + 1;
        group[6] = get_number(level + 1, row - 1);
        group[7] = group[6] + 1;
        group[8] = group[7] + 1;

        if (row == level - 1) {
                group[2] = 0;
        }
        if (row == level) {
                group[1] = 0;
                group[2] = 0;
                group[6] = 0;
        }
        return;
}

int main(int argc, const char *argv[]) {
        /* uint64_t s = 0; */
        array vec;
        kv_init(vec);
        int level = 0;
        level = atoi(argv[1]);

        uint64_t start = get_number(level - 2, 1);
        uint64_t end = get_number(level + 3, 1);

        printf("prime sieve in [%llu, %llu)\n", start, end);
        segment_sieve(start, end, &vec);
        printf("prime sieve in [%llu, %llu) finished\n", start, end);

        // check if this prime is in a 3 x 3 group

        uint64_t lstart = get_number(level, 1);
        uint64_t lend = get_number(level + 1, 1);
        array lvec;
        kv_init(lvec);
        kv_resize(int, lvec, lend - lstart);
        for (uint64_t i = 0; i < lend - lstart; i++)
                lvec.a[i] = 0;

        uint64_t sum = 0;
        uint64_t group[9] = {0};
        for (uint64_t i = level - 1; i < level + 2; i++) {
                for (uint64_t row = 1; row < level; row++) {
                        if (vec.a[get_number(i, row) - start] == 0) {
                                // center is prime
                                get_around(i, row, group);
                                int counter = 0;
                                for (int t = 0; t < 9; t++) {
                                        if (vec.a[group[t] - start] == 0)
                                                counter++;
                                }
                                if (counter >= 3) {
                                        for (int t = 0; t < 9; t++) {
                                                if (vec.a[group[t] - start] == 0 && group[t] >= lstart && group[t] < lend) {
                                                        /* printf("%llu\n", group[t]); */
                                                        lvec.a[group[t] - lstart] = 1;
                                                }
                                        }
                                }
                        }
                }
        }

        for (uint64_t i = 0; i < lend - lstart; i++) {
                if (lvec.a[i] == 1) {
                        /* printf("%llu\n", i + lstart); */
                        sum += i + lstart;
                }
        }
        printf("sum = %llu\n", sum);

        return 0;
}
