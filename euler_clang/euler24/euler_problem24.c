/*
 * =====================================================================================
 *
 *       Filename:  euler_problem24.c
 *
 *    Description:  欧拉计划24题
 *
 *        Version:  1.0
 *        Created:  2018-08-09
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

#define LIMIT 1000000

int factorial(int n) {
        int s = 1;
        for (int i = 1; i <= n; i++)
                s *= i;
        return s;
}

int main() {
        clock_t begin = clock();

        int s[10] = {0};
        int sum = LIMIT;
        int i, j;
        for (i = 0; i < 10; i++) {
                for (j = 0; factorial(9 - i) * j < sum; j++)
                        ;
                s[i] = j - 1;
                sum -= factorial(9 - i) * (j - 1);
        }

        int jump[10] = {0};
        long result = 0;
        int t;
        for (i = 0; i < 10; i++) {

                j = 0;
                t = 0;
                while (1) {
                        if (t >= s[i] && jump[j] == 0)
                                break;
                        if (jump[j++] == 0)
                                t++;
                }
                jump[j] = 1;
                result = result * 10 + j;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %ld, time use => %lfs\n", result, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
