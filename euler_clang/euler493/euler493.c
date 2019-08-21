/*
 * =====================================================================================
 *
 *       Filename:  euler493.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

ull zuhe(int m, int n) {
        ull isum = 1;
        int k;

        for (k = 1; k <= n; k++)
                isum = (isum * (m - n + k)) / k;

        return isum;
}

int main(int argc, char *argv[]) {
        double res;
        res = 1 - (double)zuhe(60, 20) / zuhe(70, 20);
        printf("%.10f\n", res * 7);
        return 0;
}
