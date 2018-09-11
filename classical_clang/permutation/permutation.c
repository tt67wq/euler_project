/*
 * =====================================================================================
 *
 *       Filename:  permutation.c
 *
 *    Description:  全排列
 *
 *        Version:  1.0
 *        Created:  2018-09-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[] = {1, 2, 3, 4};

#define N 4
#define M 3
int results[N] = {0}; //保存已经找到的结果前缀数组
int results_end = 0;  //结果前缀数组有效数据下标
int is_used[N] = {0}; //是否已经排列过了的标志

void perm(int deep, int n) {
        int i;
        if (deep > n) // 越界递归结束
        {
                return;
        }

        if (deep == n) // 找到结果，打印，递归结束
        {
                for (i = 0; i < n; i++) {
                        printf("%d", results[i]);
                }
                printf("\n");
                return;
        }

        for (i = 0; i < n; i++) {
                if (is_used[i] == 0) {
                        is_used[i] = 1;
                        results[deep] = array[i];
                        perm(deep + 1, n);
                        is_used[i] = 0;
                }
        }
}

int main() {
        perm(0, 4);
        return 0;
}
