/*
 * =====================================================================================
 *
 *       Filename:  euler_problem23.c
 *
 *    Description:  欧拉计划23题
 *
 *        Version:  1.0
 *        Created:  2018-08-08
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

#define LIMIT 28123

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
        int all[LIMIT] = {0};
        int abundants[LIMIT] = {0};
        int size = 0;
        for (int i = 0; i < LIMIT; i++) {
                if (d(i) > i)
                        abundants[size++] = i;
        }

        /* for (int i = 0; i < size; i++) */
        /*         printf("%d ", abundants[i]); */

        for (int i = 0; i < size; i++) {
                for (int j = i; j < size; j++) {
                        if (abundants[i] + abundants[j] < LIMIT)
                                all[abundants[i] + abundants[j]] = 1;
                        else
                                continue;
                }
        }
        int sum = 0;
        for (int i = 0; i < LIMIT; i++) {
                if (all[i] != 1)
                        /* printf("%d ", i); */
                        sum += i;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d, time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
