/*
 * =====================================================================================
 *
 *       Filename:  euler_problem16.c
 *
 *    Description:  欧拉计划16题
 *
 *        Version:  1.0
 *        Created:  2018-07-26
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

#define LIMIT 1000
#define SIZE 310

int main() {
        clock_t begin = clock();
        int res[SIZE] = {0};
        int sum = 0;
        res[0] = 2;
        for (int i = 1; i < LIMIT; i++) {
                for (int j = 0; j < SIZE; j++) {
                        if (res[j] > 0)
                                res[j] *= 2;
                }
                for (int j = 0; j < SIZE - 1; j++) {
                        if (res[j] >= 10) {
                                res[j + 1] += 1;
                                res[j] -= 10;
                        }
                }
        }

        for (int i = SIZE - 1; i >= 0; i--) 
                sum += res[i];
        
        clock_t end = clock();
        double timespent = end - begin;

        printf("result => %d, time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

	return 0;
}
