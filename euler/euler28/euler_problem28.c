/*
 * =====================================================================================
 *
 *       Filename:  euler_problem28.c
 *
 *    Description:  欧拉计划28题
 *
 *        Version:  1.0
 *        Created:  2018-08-14
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

#define SIZE 1001

/* 21 22 23 24 25 */
/* 20  7  8  9 10 */
/* 19  6  1  2 11 */
/* 18  5  4  3 12 */
/* 17 16 15 14 13 */

int main() {
        clock_t begin = clock();
        int matrix[SIZE][SIZE];
        int level = 1;
        int index = 1;
        int sum = 0;

        for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                        matrix[i][j] = 0;

        matrix[(SIZE - 1) / 2][(SIZE - 1) / 2] = index;
        sum += 1;

        while (1) {
                /* [(SIZE - 1) / 2 + 1 -level][(SIZE - 1) / 2 + level] */
                for (int i = 0; i < level * 2; i++)
                        matrix[(SIZE - 1) / 2 - level + 1 + i][(SIZE - 1) / 2 + level] = ++index;

                sum += matrix[(SIZE - 1) / 2 + level][(SIZE - 1) / 2 + level];

                for (int i = 0; i < level * 2; i++)
                        matrix[(SIZE - 1) / 2 + level][(SIZE - 1) / 2 + level - i - 1] = ++index;
                sum += matrix[(SIZE - 1) / 2 + level][(SIZE - 1) / 2 - level];

                for (int i = 0; i < level * 2; i++)
                        matrix[(SIZE - 1) / 2 + level - 1 - i][(SIZE - 1) / 2 - level] = ++index;

                sum += matrix[(SIZE - 1) / 2 - level][(SIZE - 1) / 2 - level];

                for (int i = 0; i < level * 2; i++)
                        matrix[(SIZE - 1) / 2 - level][(SIZE - 1) / 2 - level + i + 1] = ++index;
                sum += matrix[(SIZE - 1) / 2 - level][(SIZE - 1) / 2 + level];

                level++;
                if (level * 2 + 1 > SIZE)
                        break;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
