/*
 * =====================================================================================
 *
 *       Filename:  euler45.c
 *
 *    Description:  欧拉计划45题
 *
 *        Version:  1.0
 *        Created:  2018-10-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 1000000

int f1(int n) { return (int)((sqrt(8 * n + 1) - 1) / 2); }
int f2(int n) { return (int)((sqrt(24 * n + 1) + 1) / 6); }
int f3(int n) { return (int)(n * (2 * n - 1)); }

// 二分查找
void binary_search(int low, int high) {
        // 逃逸
        if (low + 1 == high) {
                if (f1(low) == f2(low))
                        printf("%d\n", low);
                return;
        }
        // 二分
        int mid = (low + high) / 2;
        int mid_value1 = f1(mid);
        int mid_value2 = f2(mid);

        int low1 = f1(low);
        int low2 = f2(low);

        int high1 = f1(high);
        int high2 = f2(high);

        if ((low1 <= low2 && mid_value1 >= mid_value2) ||
            (low1 >= low2 && mid_value1 <= mid_value2))
                binary_search(low, mid);
        if ((mid_value1 <= mid_value2 && high1 >= high2) ||
            (mid_value1 >= mid_value2 && high1 <= high2))
                binary_search(mid, high);
}

int main() {
        /* binary_search(1, MAXNUM); */
	printf("%d\n", f2(40755));
        return 0;
}
