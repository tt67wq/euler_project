/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-31
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getRow(int rowIndex, int *returnSize) {

        int i, j, *res;
        *returnSize = rowIndex + 1;
        res = (int *)calloc(*returnSize, sizeof(int));

        for (i = 0; i <= rowIndex; i++) {
                for (j = i; j >= 0; j--) {
                        if (j == 0 || j == i)
                                res[j] = 1;
                        else
                                res[j] += res[j - 1];
                }
        }
        return res;
}

int main() {
        int size, *res;
        int i, row;
        while (1) {
                scanf("%d", &row);
                res = getRow(row, &size);
                for (i = 0; i < size; i++)
                        printf("%d ", res[i]);
                printf("\n");
                free(res);
        }
        return 0;
}
