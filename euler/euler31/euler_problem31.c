/*
 * =====================================================================================
 *
 *       Filename:  euler_problem31.c
 *
 *    Description:  欧拉计划31题
 *
 *        Version:  1.0
 *        Created:  2018-08-17
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

int main() {
        /* int coins[8] = {1, 2, 5, 10, 20, 50, 100, 200}; */
        clock_t begin = clock();
        int sum = 0;
        for (int a1 = 0; a1 <= 200; a1++) {
                for (int a2 = 0; a2 <= 100; a2++) {
                        if (a2 * 2 + a1 > 200)
                                continue;
                        for (int a3 = 0; a3 <= 40; a3++) {
                                if (a3 * 5 + a2 * 2 + a1 > 200)
                                        continue;
                                for (int a4 = 0; a4 <= 20; a4++) {
                                        if (a4 * 10 + a3 * 5 + a2 * 2 + a1 > 200)
                                                continue;
                                        for (int a5 = 0; a5 <= 10; a5++) {
                                                if (a5 * 20 + a4 * 10 + a3 * 5 + a2 * 2 + a1 > 200)
                                                        continue;
                                                for (int a6 = 0; a6 <= 4; a6++) {
                                                        if (a6 * 50 + a5 * 20 + a4 * 10 + a3 * 5 +
                                                                a2 * 2 + a1 >
                                                            200)
                                                                continue;

                                                        for (int a7 = 0; a7 <= 2; a7++) {
                                                                if (a1 + a2 * 2 + a3 * 5 +
                                                                        a4 * 10 + a5 * 20 +
                                                                        a6 * 50 + a7 * 100 ==
                                                                    200)
                                                                        sum += 1;
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", sum + 1, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
