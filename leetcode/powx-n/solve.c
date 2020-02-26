/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-02-26
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

double myPow2(double x, long n) {
        double t;

        if (n < 0) {
                x = 1 / x;
                n = -n;
        }

        if (n == 0) {
                return 1;
        } else if ((n & 0x01) == 0) {
                t = myPow2(x, n >> 1);
                return t * t;
        } else {
                return x * myPow2(x, n - 1);
        }
}
double myPow(double x, int n) { return myPow2(x, (long)n); }

int main() { return 0; }
