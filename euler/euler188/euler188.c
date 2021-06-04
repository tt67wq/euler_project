/*
 * =====================================================================================
 *
 *       Filename:  euler188.c
 *
 *    Description:  欧拉计划188
 *
 *        Version:  1.0
 *        Created:  2019-04-02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 计算 m^n % k
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
        if (n % 2 == 0) {
                return pow_mod(b, n / 2, k);
        } else {
                return (m * pow_mod(b, (n - 1) / 2, k)) % k;
        }
}

uint64_t tet_mod(uint64_t m, uint64_t n, uint64_t k) {
        if (n == 1)
                return m % k;

        return pow_mod(m, tet_mod(m, n - 1, k), k);
}

int main() {
        double dtime = clock();
        printf("%llu\n", tet_mod(1777, 1855, 100000000));
        dtime = (double)(clock() - dtime) / CLOCKS_PER_SEC;
        printf("time=%.3lf sec.\n", dtime);
        return 0;
}
