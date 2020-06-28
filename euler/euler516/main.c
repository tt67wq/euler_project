/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

// https://pe-cn.github.io/516/

#define MAX 1000000000000

int eular(int n) {
        int ret = 1, i;
        for (i = 2; i * i <= n; i++) {
                if (n % i == 0) {
                        n /= i, ret *= i - 1;
                        while (n % i == 0)
                                n /= i, ret *= i;
                }
        }
        if (n > 1)
                ret *= n - 1;
        return ret;
}

int main() {
        // all Hamming numbers less than 10^12
        for (int i = 0; i < 40; i++) {
                for (int j = 0; pow(2, i) * pow(3, j) < MAX; j++) {
                        printf("%d %d %ld\n", i, j,
                               (unsigned long)pow(2, i) * (unsigned long)pow(3, j));
                }
        }

        return 0;
}