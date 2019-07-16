/*
 * =====================================================================================
 *
 *       Filename:  1007.c
 *
 *    Description:  zoj 1007
 *
 *        Version:  1.0
 *        Created:  2019-07-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

double sum, a;

void hamming() {}

int main() {
        double k;
        for (a = 0.000; a < 2.000; a = a + 0.001) {
                sum = 0;
                for (k = 1; k < 10000; k++) {
                        sum = sum + (1 - a) / (k * (k + 1) * (k + a));
                }
                sum = sum + (1 - a) / (2 * 10000 * 10000) + 1.0;
                printf("%5.3f %16.12f\n", a, sum);
        }
        return 0;
}
