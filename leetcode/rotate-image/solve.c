/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-27
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void rotate(int **matrix, int matrixSize, int *matrixColSize) {
        if (matrixSize == 1 || matrixSize == 0)
                return;

        int i, l = 0;
        int *tmp;

        tmp = (int *)calloc(matrixSize, sizeof(int));

        for (l = 0; 2 * l < matrixSize; l++) {
                if (matrixSize - 2 * l > 1) {
                        for (i = l; i < matrixSize - l; i++) {
                                tmp[i] = matrix[l][i];
                        }

                        // left to top
                        for (i = l; i < matrixSize - l; i++)
                                matrix[l][matrixSize - 1 - i] = matrix[i][l];

                        // bottom to left
                        for (i = l; i < matrixSize - l; i++)
                                matrix[i][l] = matrix[matrixSize - 1 - l][i];

                        // right to bottom
                        for (i = l; i < matrixSize - l; i++)
                                matrix[matrixSize - 1 - l][i] = matrix[matrixSize - 1 - i][matrixSize - 1 - l];

                        // tmp to right
                        for (i = l; i < matrixSize - l; i++)
                                matrix[matrixSize - 1 - i][matrixSize - 1 - l] = tmp[matrixSize - 1 - i];
                }
        }
        return;
}

int main() {
        int **matrix;
        matrix = (int **)calloc(3, sizeof(int *));
        matrix[0] = (int *)calloc(3, sizeof(int));
        matrix[0][0] = 1;
        matrix[0][1] = 2;
        matrix[0][2] = 3;

        matrix[1] = (int *)calloc(3, sizeof(int));
        matrix[1][0] = 4;
        matrix[1][1] = 5;
        matrix[1][2] = 6;

        matrix[2] = (int *)calloc(3, sizeof(int));
        matrix[2][0] = 7;
        matrix[2][1] = 8;
        matrix[2][2] = 9;

        rotate(matrix, 3, NULL);

        int i, j;
        for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                        printf("%d ", matrix[i][j]);
                }
                printf("\n");
        }

        return 0;
}
