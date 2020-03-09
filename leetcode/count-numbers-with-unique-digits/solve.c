/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-09
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int choose(int m, int n) {
        int k, isum;
        isum = 1;
        for (k = 1; k <= n; k++) {
                isum = (isum * (m - n + k)) / k; //先算乘法，避免先算（m-n+k）/k除不尽带来误差
        }
        return isum;
}

int factorial(int n) {
        int s = 1;
        for (; n > 0; n--) {
                s *= n;
        }
        return s;
}

int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
                return 1;
        }
        if (n == 1) {
                return 10;
        }
        int a, b, s, m;
        s = 10;
        for (m = 2; m <= n; m++) {
                a = choose(9, m);     // no 0
                b = choose(9, m - 1); // contains 0
                s += (a * factorial(m) + b * factorial(m - 1) * (m - 1));
        }
        return s;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", countNumbersWithUniqueDigits(n));
        }
        return 0;
}
