/*
 * =====================================================================================
 *
 *       Filename:  zuhe.c
 *
 *    Description:  计算组合数
 *
 *        Version:  1.0
 *        Created:  2018-09-29
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

int main(int argc, char *argv[]) {
        ull isum = 1;
        int m, n, k;

        printf("input m=");
        scanf("%d", &m);
        printf("input n=");
        scanf("%d", &n);

        for (k = 1; k <= n; k++) {
                isum = (isum * (m - n + k)) / k; //先算乘法，避免先算（m-n+k）/k除不尽带来误差
        }

        printf("C(%d, %d) = %llu\n", m, n, isum);

        return 0;
}
