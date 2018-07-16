/*
 * =====================================================================================
 *
 *       Filename:  euler_problem12.c
 *
 *    Description:  欧拉计划12题
 *
 *        Version:  1.0
 *        Created:  2018-07-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include "hashmap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// 质因数分解
void factorize(int num, int *facs, int *len) {
        int i, j = 0;
        for (i = 2; i <= sqrt(num); i++) {
                if (num % i == 0) {
                        num /= i;
                        facs[j++] = i--;
                }
        }
        facs[j] = num;
        *len = j;
}

int main() {
        int num;
        printf("请输入想分解的数字: \n");
        scanf("%d", &num);
        int *facs = (int *)malloc(500 * sizeof(int));
        int len;
        factorize(num, facs, &len);
        hmap_t hmap = hashmap_create();
        for (int i = 0; i < len; i++) {
        }

        return 0;
}
