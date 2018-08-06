/*
 * =====================================================================================
 *
 *       Filename:  euler_problem19.c
 *
 *    Description:  欧拉计划19题
 *
 *        Version:  1.0
 *        Created:  2018-08-02
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
#define MAX 200

void mul(int num, int *res) {
        for (int i = 0; i < MAX; i++) {
                res[i] = res[i] * num;
        }
        for (int i = 0; i < MAX; i++) {
                if (res[i] > 10) {
                        res[i + 1] += res[i] / 10;
                        res[i] = res[i] % 10;
                }
        }
}

int main() {
	clock_t begin = clock();
        int *res = (int *)malloc(sizeof(int) * MAX); // 存放结果
        res[0] = 1;
        for (int i = 1; i < MAX; i++)
                res[i] = 0;

        for (int num = 1; num <= 100; num++)
                mul(num, res);

        int sum = 0;
        for (int j = 0; j < MAX; j++)
                sum += res[j];

        free(res);
	clock_t end = clock();
        double timespent = end - begin;
	printf("result => %d, time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
