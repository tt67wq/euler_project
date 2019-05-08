/*
 * =====================================================================================
 *
 *       Filename:  euler198.c
 *
 *    Description:  欧拉计划198题
 *
 *        Version:  1.0
 *        Created:  2019-05-07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint64_t gcd(uint64_t m, uint64_t n) {
        uint64_t r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int main(int argc, const char *argv[]) {
        uint64_t counter = 0;
        for (uint64_t m1 = 101; m1 * m1 < 5 * 1e7; m1++) {
                for (uint64_t m2 = m1 + 1; m2 * m1 < 5 * 1e7; m2++) {
                        uint64_t q = m1 * m2 * 2;
                }
        }
}
