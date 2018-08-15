/*
 * =====================================================================================
 *
 *       Filename:  euler_problem29.c
 *
 *    Description:  欧拉计划29题
 *
 *        Version:  1.0
 *        Created:  2018-08-15
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

#define LIMIT 100

void factor(int num, int *facs) {
        int i;
        for (i = 2; i <= num; i++) {
                while (num % i == 0) {
                        facs[i]++;
                        num /= i;
                }
        }
}

int main() {
        clock_t begin = clock();
        int index = 0;
        int comb[LIMIT * LIMIT][2];
        for (int i = 2; i < LIMIT + 1; i++) {
                for (int j = 2; j < LIMIT + 1; j++) {
                        comb[index][0] = i;
                        comb[index++][1] = j;
                }
        }
        int count = 0;
        int comb2[index][LIMIT + 1];
        for (int i = 0; i < index; i++) {
                for (int j = 0; j < LIMIT + 1; j++)
                        comb2[i][j] = 0;
        }
        for (int i = 0; i < index; i++) {
                int facs[LIMIT + 1] = {0};
                factor(comb[i][0], facs);
                for (int j = 0; j < LIMIT + 1; j++) {
                        if (facs[j] > 0) {
                                facs[j] *= comb[i][1];
                        }
                }

                // 检测去重
                int repeat;

                for (int z = 0; z < i; z++) {
                        repeat = 1; // 默认重复
                        int j;
                        for (j = 0; j < LIMIT + 1; j++) {
                                if (comb2[z][j] != facs[j]) {
                                        repeat = 0;
                                        break;
                                }
                        }
                        if (repeat == 1)
                                break;
                }

                if (repeat == 0) {
                        count++;
                        for (int j = 0; j < LIMIT + 1; j++) {
                                comb2[i][j] = facs[j];
                        }
                }
        }

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", count, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
