/*
 * =====================================================================================
 *
 *       Filename:  euler_problem26.c
 *
 *    Description:  欧拉计划26题
 *
 *        Version:  1.0
 *        Created:  2018-08-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 循环圈大小
int recurring_size(int n, int m) {
        int cache[2000] = {0};
        n = n % m;
        for (int i = 0;; i++) {
                cache[i] = n;
                n *= 10;
                n %= m;
                if (n == 0)
                        return 0; // 不循环
                // 检测是否循环
                int start = 0;
                for (int j = 0; j <= i; j++) {
                        if (cache[j] == n && start == 0) {
                                start = j;
                                continue;
                        }

                        if (cache[j] == n && start > 0)
                                return j - start;
                }
        }
}

int main() {
        clock_t begin = clock();
        int mx = 0;
        int mxr = 0;
        for (int n = 2; n < 1000; n++) {
                int r = recurring_size(1, n);
                printf("cycle size of %d ==> %d\n", n, r);
                if (r > mxr) {
                        mxr = r;
                        mx = n;
                }
        }

        clock_t end = clock();
        double timespent = end - begin;

        printf("result => %d, longest cycle => %d time use => %lfs\n", mx, mxr,
               (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
