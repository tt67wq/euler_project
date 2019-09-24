/*
 * =====================================================================================
 *
 *       Filename:  euler63.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
        int i, j, count = 0;
        for (j = 1; j < 30; j++) {
                for (i = 1; i < 10; i++) {
                        double n = pow(i, j);
                        int lg = (int)log10(n) + 1;
                        if (lg > j)
                                break;
                        if (lg == j) {
                                count++;
                                printf("%.0f (%d) = %d^%d\n", n, (int)log10l(n) + 1, i, j);
                        }
                }
        }
        printf("count %d\n", count);
        return 0;
}
