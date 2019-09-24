/*
 * =====================================================================================
 *
 *       Filename:  euler_problem44.c
 *
 *    Description:  欧拉计划44题
 *
 *        Version:  1.0
 *        Created:  2018-09-27
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

int pentagon(int n) { return n * (3 * n - 1) / 2; }

// 二分搜索
int binary_search(int target, int *list, int start, int end) {
        int mid = list[(start + end) / 2];
        if (mid == list[start] || mid == list[end])
                return 0;
        if (target == mid)
                return (start + end) / 2;
        if (target > mid)
                return binary_search(target, list, (start + end) / 2, end);
        if (target < mid)
                return binary_search(target, list, start, (start + end) / 2);
        return 0;
}

int check(int index, int *acc) {
        int p1 = pentagon(index);
        int i = index - 1;
        while (i > 0) {
                int p2 = pentagon(i);
                if (binary_search(p1 - p2, acc, 0, index - 1) &&
                    binary_search(p1 - 2 * p2, acc, 0, index - 1))
                        return p1 - p2 * 2;
                i--;
        }
        return 0;
}

int main() {
        clock_t begin = clock();
        int acc[10000] = {0};
        int index = 1;
        int res = 0;
        while (1) {
                if ((res = check(index, acc)) > 0)
                        break;

                // not satisfy
                acc[index] = pentagon(index);
                index++;
        }

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", res, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
