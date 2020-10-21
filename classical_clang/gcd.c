/*
 * =====================================================================================
 *
 *       Filename:  gcd.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

int lcm(int m, int n) { return m * (n / gcd(m, n)); }

/* 求最大公约数, 欧几里得算法 */
int gcd(int m, int n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

/* 扩展欧几里得算法 */
/* ax + by = gcd(a, b)的一组解 */
void extend_gcd(int a, int b, int *g, int *x, int *y) {
        if (!b) {
                *g = a;
                *x = 1;
                *y = 0;
        } else {
                gcd(b, a % b, g, y, x);
                *y -= *x * (a / b);
        }
}

int main() { return 0; }
