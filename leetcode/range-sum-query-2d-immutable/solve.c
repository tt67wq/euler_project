/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-19
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int **matrix;
        int matrixSize;
} NumMatrix;

NumMatrix *numMatrixCreate(int **matrix, int matrixSize, int *matrixColSize) {
        NumMatrix *mt;
        int i, j, s;

        mt = (NumMatrix *)calloc(1, sizeof(NumMatrix));
        mt->matrix = (int **)calloc(matrixSize, sizeof(int *));
        mt->matrixSize = matrixSize;

        for (i = 0; i < matrixSize; i++) {
                mt->matrix[i] = (int *)calloc(matrixColSize[i] + 1, sizeof(int));
                s = 0;
                for (j = 1; j <= matrixColSize[i]; j++) {
                        s += matrix[i][j - 1];
                        mt->matrix[i][j] = s;
                }
        }
        return mt;
}

int numMatrixSumRegion(NumMatrix *obj, int row1, int col1, int row2, int col2) {
        int i, s;
        s = 0;
        for (i = row1; i <= row2; i++)
                s += obj->matrix[i][col2 + 1] - obj->matrix[i][col1];
        return s;
}

void numMatrixFree(NumMatrix *obj) {
        int i;
        for (i = 0; i < obj->matrixSize; i++)
                free(obj->matrix[i]);
        free(obj);
}

int main() { return 0; }
