/*
 * =====================================================================================
 *
 *       Filename:  euler345.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 15

int matrix[N][N];

int diagonal_sum() {
        int i, s = 0;
        for (i = 0; i < N; i++) {
                s += matrix[i][i];
        }
        return s;
}

void swap(int r1, int r2) {
        int tmp[N];
        memcpy(tmp, matrix[r1], sizeof(int) * N);
        memcpy(matrix[r1], matrix[r2], sizeof(int) * N);
        memcpy(matrix[r2], tmp, sizeof(int) * N);
}
void bubble() {
        int i, j;
        int sum, tmp, maxs = 0;
        while (1) {
                for (i = 0; i < N; i++) {
                        sum = diagonal_sum();
                        for (j = 0; j < N; j++) {
                                if (i == j)
                                        continue;
                                swap(i, j);
                                tmp = diagonal_sum();
                                if (tmp > sum) {
                                        break;
                                } else {
                                        swap(i, j);
                                }
                        }
                }
                if (sum > maxs) {
                        maxs = sum;
                } else {
                        break;
                }
        }
}

int main() {
        int r;
        for (r = 0; r < N; r++) {
                scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &matrix[r][0], &matrix[r][1], &matrix[r][2], &matrix[r][3], &matrix[r][4], &matrix[r][5], &matrix[r][6], &matrix[r][7],
                      &matrix[r][8], &matrix[r][9], &matrix[r][10], &matrix[r][11], &matrix[r][12], &matrix[r][13], &matrix[r][14]);
                /* scanf("%d %d %d %d %d", &matrix[r][0], &matrix[r][1], &matrix[r][2], &matrix[r][3], &matrix[r][4]); */
        }
        bubble();
        printf("%d\n", diagonal_sum());
        return 0;
}
