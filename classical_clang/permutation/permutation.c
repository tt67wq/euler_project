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

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

void perm(int deep, int n, int *array, int *results, int *is_used) {
        int i;
        // 越界递归结束
        if (deep > n)
                return;

        if (deep == n) {
                // 找到结果，打印，递归结束
                // 也可以结果保存在一个数组里面
                for (i = 0; i < n; i++) {
                        printf("%d ", results[i]);
                }
                printf("\n");
                return;
        }

        for (i = 0; i < n; i++) {
                if (is_used[i] == 0) {
                        is_used[i] = 1;
                        results[deep] = array[i];
                        perm(deep + 1, n, array, results, is_used);
                        is_used[i] = 0;
                }
        }
}

int main() {
        int array[4] = {1, 2, 3, 4};
        int results[4] = {0};
        int is_used[4] = {0};
        perm(0, 4, array, results, is_used);
        return 0;
}
