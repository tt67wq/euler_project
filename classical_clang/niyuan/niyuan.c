/*
 * =====================================================================================
 *
 *       Filename:  niyuan.c
 *
 *    Description:  扩展欧几里得算法求逆元
 *
 *        Version:  1.0
 *        Created:  2019-04-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int extend_gcd(int a, int b) {
        int a1 = 0;
        int a2 = 1;

        int b1 = 1;
        int b2 = 0;

        while (b) {
                int c = a / b;
                int tmp = a;
                a = b;
                b = tmp % b;

                tmp = a1;
                a1 = a2 - c * a1;
                a2 = tmp;

                tmp = b1;
                b1 = b2 - c * b1;
                b2 = tmp;
        }
        return a2;
}

int niyuan(int a, int b) {
        int g = extend_gcd(a, b);
        return g > 0 ? g : b + g;
}

int main(int argc, const char *argv[]) {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);

        int c = niyuan(a, b);
        printf("niyuan(%d, %d) = %d\n", a, b, c);

        return 1;
}
