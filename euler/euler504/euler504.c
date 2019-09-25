/*
 * =====================================================================================
 *
 *       Filename:  euler504.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void gcd(int a, int b, int *g, int *x, int *y) {
        if (!b) {
                *g = a;
                *x = 1;
                *y = 0;
        } else {
                gcd(b, a % b, g, y, x);
                *y -= *x * (a / b);
        }
}

int main() {

        int g, x, y;
        int a, b;
        while (1) {
                scanf("%d %d", &a, &b);
                gcd(a, b, &g, &x, &y);
                printf("x=%d y=%d g=%d\n", x, y, g);
        }
        return 0;
}
