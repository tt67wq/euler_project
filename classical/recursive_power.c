/*
 * =====================================================================================
 *
 *       Filename:  recursive_power.c
 *
 *    Description:  递归求乘方
 *
 *        Version:  1.0
 *        Created:  2018-07-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

int recursive_power(int m, int n) {
        int temp;

        if (n == 0) /* m^0 = 1                  */
                return 1;
        else if ((n & 0x01) == 0) { /* if power is even then */
                temp = recursive_power(m, n >> 1);
                return temp * temp; /* m^(2k) = (m^k)^2         */
        } else                      /* otherwise, m^n=m*m^(n-1) */
                return m * recursive_power(m, n - 1);
}

int main() {
        int m, n;
        int temp;
        printf("input m: ");
        scanf("%d", &m);
        printf("input n: ");
        scanf("%d", &n);
        printf("%d^%d = %d", m, n, recursive_power(m, n));
        printf("\n");

        return 0;
}
