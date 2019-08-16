/*
 * =====================================================================================
 *
 *       Filename:  gridland.c
 *
 *    Description:  zoj 1037
 *
 *        Version:  1.0
 *        Created:  2019-08-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define R2 1.4142135623730951

int m, n;

double solve() {
        if (m % 2 == 1 && n % 2 == 1) {
                return m * n - 1 + R2;
        } else {
                return m * n;
        }
}

int main() {
        int num, i = 1;
        scanf("%d", &num);
        while (num > 0) {
                scanf("%d %d", &m, &n);
                printf("Scenario #%d:\n", i++);
                printf("%.02f\n", solve());
                printf("\n");
                num--;
        }
        return 0;
}
