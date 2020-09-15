/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-15
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **transpose(int **A, int ASize, int *AColSize, int *returnSize, int **returnColumnSizes) {
        int **ans = (int **)calloc(AColSize[0], sizeof(int *));
        for (int i = 0; i < AColSize[0]; i++) {
                ans[i] = (int *)calloc(ASize, sizeof(int));
                for (int j = 0; j < ASize; j++) {
                        ans[i][j] = A[j][i];
                }
                (*returnColumnSizes)[i] = ASize;
        }
        (*returnSize) = AColSize[0];
        return ans;
}

int main() { return 0; }