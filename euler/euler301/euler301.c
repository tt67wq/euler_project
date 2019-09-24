/*
 * =====================================================================================
 *
 *       Filename:  euler301.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int zuhe(int m, int n) {
        int isum = 1;
        int k;
        for (k = 1; k <= n; k++) {
                isum = (isum * (m - n + k)) / k;
        }
        return isum;
}

int main() {
        int i, s = 0;
        for (i = 1; i < 16; i++) {
                s += zuhe(31 - i, i);
        }
        printf("%d\n", s + 1);
        return 0;
}
