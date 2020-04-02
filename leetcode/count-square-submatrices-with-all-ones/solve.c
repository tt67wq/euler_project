/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-02
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c) {
        int m = INT_MAX;
        m = a < m ? a : m;
        m = b < m ? b : m;
        m = c < m ? c : m;
        return m;
}

int countSquares(int **matrix, int matrixSize, int *matrixColSize) {
        int ans = 0;
        for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixColSize[0]; j++) {
                        if (i && j && matrix[i][j]) {
                                matrix[i][j] +=
                                    min(matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1]);
                        }
                        ans += matrix[i][j];
                }
        }
        return ans;
}

int main() { return 0; }
