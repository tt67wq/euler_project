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

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>

typedef kvec_t(int) array;

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

int qpow(int x, int n, int mod) {
        int res = 1;
        while (n) {
                /* printf(" x = %d, n = %d, res = %d \n", x, n, res); */
                if (n & 1)
                        res = (res * x) % mod;
                x = (x * x) % mod;
                n >>= 1;
        }
        return res;
}

// 阶乘逆元 max!*x = 1 mod m
void fac_niyuan(int max, int mod, array *facs, array *inv_facs) {
        kv_push(int, *facs, 1);
        for (int i = 1; i <= max; i++)
                kv_push(int, *facs, kv_A(*facs, i - 1) * i % mod);

        kv_resize(int, *inv_facs, max + 1);
        inv_facs->a[max] = qpow(kv_A(*facs, max), mod - 2, mod);
        for (int i = max - 1; i >= 0; i--)
                inv_facs->a[i] = (inv_facs->a[i + 1] * (i + 1)) % mod;
}

int main(int argc, const char *argv[]) {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);

        int c = niyuan(a, b);
        printf("niyuan(%d, %d) = %d\n", a, b, c);

        array facs;
        array inv_facs;
        kv_init(facs);
        kv_init(inv_facs);
        fac_niyuan(5, 17, &facs, &inv_facs);

        for (int i = 0; i < 6; i++) {
                printf("%d %d\n", kv_A(facs, i), kv_A(inv_facs, i));
        }

        return 1;
}
