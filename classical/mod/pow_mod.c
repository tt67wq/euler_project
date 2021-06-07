/*
 * =====================================================================================
 *
 *       Filename:  pow_mod.c
 *
 *    Description:  同余定理
 *
 *        Version:  1.0
 *        Created:  2018-07-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 计算 m^n % k
intmax_t pow_modulo(intmax_t a, intmax_t b, const int n) {
        intmax_t x = 1, y = a;
        while (b > 0) {
                if (b & 1) {
                        x = (x * y) % n; // multiplying with base
                }
                y = (y * y) % n; // squaring the base
                b = b >> 1;
        }
        return x % n;
}


int main() {
        int m, n, k, r;
        printf("输入 m^n %% k 中的m\n");
        scanf("%d", &m);
        printf("输入 m^n %% k 中的n\n");
        scanf("%d", &n);
        printf("输入 m^n %% k 中的k\n");
        scanf("%d", &k);

        r = pow_modulo(m, n, k);
        printf("结果为: %d\n", r);
        return 0;
}
