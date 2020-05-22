/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-22
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

bool isToeplitzMatrix(int **matrix, int matrixSize, int *matrixColSize) {

        // 纵向
        for (int i = matrixSize - 2; i >= 0; i--) {
                int j = 0;
                int k = i;
                int m = matrix[i][j];

                while (k < matrixSize - 1 && j < matrixColSize[0] - 1) {
                        k++;
                        j++;
                        if (m != matrix[k][j]) {
                                return false;
                        }
                }
        }

        // 横向
        for (int j = 1; j < matrixColSize[0]; j++) {
                int k = j;
                int i = 0;
                int m = matrix[i][k];

                while (i < matrixSize - 1 && k < matrixColSize[0] - 1) {
                        k++;
                        i++;
                        if (m != matrix[i][k]) {
                                return false;
                        }
                }
        }

        return true;
}

int main() {
        int m1[] = {1, 2, 3, 4};
        int m2[] = {5, 1, 2, 3};
        int m3[] = {9, 5, 1, 2};
        int *matrix[3] = {m1, m2, m3};
        int matrixColSize[3] = {4, 4, 4};

        printf("%d\n", isToeplitzMatrix(matrix, 3, matrixColSize));
        return 0;
}
