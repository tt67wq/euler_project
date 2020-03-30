/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-30
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
int **reconstructMatrix(int upper, int lower, int *colsum, int colsumSize, int *returnSize,
                        int **returnColumnSizes) {

        int **ans = (int **)calloc(2, sizeof(int *));
        for (int i = 0; i < 2; i++) {
                ans[i] = (int *)calloc(colsumSize, sizeof(int));
        }

        int uu, ll;
        uu = 0;
        ll = 0;
        for (int i = 0; i < colsumSize; i++) {
                if (colsum[i] == 2) {
                        ans[0][i] = 1;
                        ans[1][i] = 1;
                        uu++;
                        ll++;
                        continue;
                }
                if (colsum[i] == 0) {
                        ans[0][i] = 0;
                        ans[1][i] = 0;
                        continue;
                }
                if (colsum[i] == 1) {
                        ans[0][i] = 1;
                        ans[1][i] = 0;
                        uu++;
                }
        }

        for (int i = 0; i < colsumSize && uu > upper; i++) {
                if (colsum[i] == 1) {
                        ans[0][i] = 0;
                        ans[1][i] = 1;
                        uu--;
                        ll++;
                }
        }

        printf("uu: %d, ll: %d\n", uu, ll);
        if (uu == upper && ll == lower) {
                *returnSize = 2;
                (*returnColumnSizes)[0] = colsumSize;
                (*returnColumnSizes)[1] = colsumSize;
                return ans;
        }
        *returnSize = 0;
        return NULL;
}

int main() {
        int colsum[] = {1, 1, 1};
        int colsumSize = 3;
        int returnSize = 0;
        int *returnColumnSizes = (int *)calloc(2, sizeof(int));
        int **ans = reconstructMatrix(2, 1, colsum, colsumSize, &returnSize, &returnColumnSizes);
        printf("returnSize: %d\n", returnSize);
        if (ans != NULL) {
                for (int i = 0; i < colsumSize; i++) {
                        printf("%d ", ans[0][i]);
                }
                printf("\n");
                for (int i = 0; i < colsumSize; i++) {
                        printf("%d ", ans[1][i]);
                }
                printf("\n");
                free(ans[0]);
                free(ans[1]);
                free(ans);
        }
        free(returnColumnSizes);
        return 0;
}
