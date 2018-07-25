/*
 * =====================================================================================
 *
 *       Filename:  euler_problem15.c
 *
 *    Description:  欧拉计划15题
 *
 *        Version:  1.0
 *        Created:  2018-07-25
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

#define MAXSIZE 40

// 生成帕斯卡三角
void pascal_triangle(long mat[MAXSIZE][MAXSIZE]) {
        mat[0][0] = 1;
        mat[1][0] = 1;
        mat[1][1] = 1;

        for (int i = 2; i < MAXSIZE; i++) {
                mat[i][0] = 1;
                mat[i][i] = 1;
                for (int j = 1; j < i; j++) {
                        mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
                }
        }
        return;
}

int main() {
        clock_t begin = clock();
        long mat[MAXSIZE][MAXSIZE];
        for (int i = 0; i < MAXSIZE; i++)
                for (int j = 0; j < MAXSIZE; j++)
                        mat[i][j] = 0;
        pascal_triangle(mat);
        clock_t end = clock();
        double timespent = end - begin;

        printf("result => %ld, time use => %lfs\n", mat[2 * 20][20], (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
