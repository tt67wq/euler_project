/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Leonhard Euler was born on 15 April 1707.

// Consider the sequence 1504170715041707n mod 4503599627370517.

// An element of this sequence is defined to be an Eulercoin if it is strictly smaller than all
// previously found Eulercoins.

// For example, the first term is 1504170715041707 which is the first Eulercoin.
// The second term is 3008341430083414 which is greater than 1504170715041707 so is not an
// Eulercoin. However, the third term is 8912517754604 which is small enough to be a new Eulercoin.

// The sum of the first 2 Eulercoins is therefore 1513083232796311.

// Find the sum of all Eulercoins.

#define N 1504170715041707L

typedef unsigned long ul;

int main() {

        ul c1 = N, c2 = 8912517754604;
        ul coinSum = c1 + c2;

        while (c2 > 0) {
                ul delta = c1 - c2;
                c1 = c2;
                while (c2 < delta) {
                        c2 += c1;
                }
                c2 -= delta;
                coinSum += c2;
                printf("%lu\n", c2);
        }
        printf("%lu\n", coinSum);

        return 0;
}