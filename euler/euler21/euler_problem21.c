/*
 * =====================================================================================
 *
 *       Filename:  euler_problem21.c
 *
 *    Description:  欧拉计划21题
 *
 *        Version:  1.0
 *        Created:  2018-08-03
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

int d(int n) {
        int s = 0;
        for (int i = 1; i <= n / 2; i++) {
                if (n % i == 0)
                        s += i;
        }
        return s;
}

int main() {
        clock_t begin = clock();
        int sum = 0;
        int jump[100000] = {0};
        for (int i = 2; i < 10000; i++) {
                if (jump[i] == 1)
                        continue;
                int t1 = d(i);
                int t2 = d(t1);
                jump[t1] = 1;
                if (i == t2 && t1 != i) {
                        printf("%d <> %d\n", i, t1);
                        sum += i;
                        sum += t1;
                }
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d, time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
