/*
 * =====================================================================================
 *
 *       Filename:  factor.c
 *
 *    Description:  因试分解
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

int main() {
        int n, i;
        printf("Plz input int: ");
        scanf("%d", &n);
        printf("%d=", n);
        for (i = 2; i <= n; i++)
                while (n % i == 0) {
                        printf("%d", i);
                        n /= i;
                        if (n != 1)
                                printf("*");
                }
        printf("\n");
        return 0;
}
