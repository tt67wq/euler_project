/*
 * =====================================================================================
 *
 *       Filename:  wheel_base.c
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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

// wheel-based prime test
bool isPrime(unsigned long long x) {
        // prime test for 2, 3 and 5 and their multiples
        if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0)
                return x == 2 || x == 3 || x == 5;

        // wheel with size 30 (=2*3*5):
        // test against 30m+1, 30m+7, 30m+11, 30m+13, 30m+17, 30m+19, 30m+23, 30m+29
        // their deltas/increments are:
        const unsigned int Delta[] = {6, 4, 2, 4, 2, 4, 6, 2};
        // start with 7, which is 30*0+7
        unsigned long long i = 7;
        // 7 belongs to the second test group
        int pos = 1;

        // check numbers up to sqrt(x)
        while (i * i <= x) {
                // not prime ?
                if (x % i == 0)
                        return false;

                // skip forward to next test divisor
                i += Delta[pos];
                // next delta/increment
                pos = (pos + 1) & 7;
        }

        // passed all tests, must be a prime number
        return x > 1;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", isPrime(n));
        }
        return 0;
}