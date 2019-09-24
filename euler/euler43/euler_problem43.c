/*
 * =====================================================================================
 *
 *       Filename:  euler_problem43.c
 *
 *    Description:  欧拉计划43题
 *
 *        Version:  1.0
 *        Created:  2018-09-12
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

long list2num(int *list, int len) {
        long num = 0;
        for (int i = 0; i < len; i++) {
                num = num * 10 + list[i];
        }
        return num;
}

int check_digits(int *digits) {
        int d2[3] = {digits[1], digits[2], digits[3]};
        if (list2num(d2, 3) % 2 != 0)
                return 0;
        int d3[3] = {digits[2], digits[3], digits[4]};
        if (list2num(d3, 3) % 3 != 0)
                return 0;
        int d4[3] = {digits[3], digits[4], digits[5]};
        if (list2num(d4, 3) % 5 != 0)
                return 0;
        int d5[3] = {digits[4], digits[5], digits[6]};
        if (list2num(d5, 3) % 7 != 0)
                return 0;
        int d6[3] = {digits[5], digits[6], digits[7]};
        if (list2num(d6, 3) % 11 != 0)
                return 0;
        int d7[3] = {digits[6], digits[7], digits[8]};
        if (list2num(d7, 3) % 13 != 0)
                return 0;
        int d8[3] = {digits[7], digits[8], digits[9]};
        if (list2num(d8, 3) % 17 != 0)
                return 0;

        return 1;
}

void perm(int deep, int n, int *array, int *results, int *is_used, long *sum) {
        int i;
        if (deep > n) // 越界递归结束
        {
                return;
        }

        if (deep == n) // 找到结果
        {
                if (check_digits(results)) {
                        long tmp = list2num(results, 10);
                        printf("%ld\n", tmp);
                        *sum += tmp;
                }

                return;
        }

        for (i = 0; i < n; i++) {
                if (is_used[i] == 0) {
                        is_used[i] = 1;
                        results[deep] = array[i];
                        perm(deep + 1, n, array, results, is_used, sum);
                        is_used[i] = 0;
                }
        }
}

int main() {
	clock_t begin = clock();
        int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int is_used[10] = {0};
        int results[10] = {0};
        long sum = 0;
        perm(0, 10, array, results, is_used, &sum);

	clock_t end = clock();
        double timespent = end - begin;
        printf("result => %ld time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
