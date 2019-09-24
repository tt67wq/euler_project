/*
 * =====================================================================================
 *
 *       Filename:  euler48.c
 *
 *    Description:  欧拉计划48题
 *
 *        Version:  1.0
 *        Created:  2018-11-19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
typedef unsigned long long uint64_t;

uint64_t modular_exponentiation(uint64_t n, uint64_t exp, const uint64_t mod) {
        if (mod == 1)
                return 0;
        if (exp == 0)
                return 1;
        uint64_t result = 1;
        n %= mod;
        while (exp > 0) {
                result = (result * n) % mod;
                --exp;
        }
        return result;
}

int main(int argc, const char *argv[]) {

        const uint64_t mod = (uint64_t)1e10;
        uint64_t result = 0;
        for (int i = 1; i < 1001; ++i) {
                result += modular_exponentiation(i, i, mod);
                if (result > mod)
                        result %= mod;
        }
        printf("The last ten digits in the series: %llu\n", result);

        return 0;
}
