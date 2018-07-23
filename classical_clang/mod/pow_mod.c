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

// 计算 m^n % k
int pow_mod(int m, int n, int k) {
        if (n == 1)
                return m % k;
        if (n == 2)
                return (m * m) % k;

        if (m % k == 0)
                return 0;

        int b = pow_mod(m, 2, k);
        if (n % 2 == 0) {

                return pow_mod(b, n / 2, k);
        } else {
                return pow_mod(b, (n - 1) / 2, k) % k;
        }
}

int main() {
        int m, n, k, r;
        printf("输入 m^n %% k 中的m\n");
        scanf("%d", &m);
        printf("输入 m^n %% k 中的n\n");
        scanf("%d", &n);
        printf("输入 m^n %% k 中的k\n");
        scanf("%d", &k);

        r = pow_mod(m, n, k);
        printf("结果为: %d\n", r);
        return 0;
}
