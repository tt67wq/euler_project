/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-11
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

int buff[10];

void dfs(int idx, int k, int s, int n, int ***res, int *returnSize) {
        if (idx == k) {
                if (s == n) {
                        int *res0 = (int *)calloc(k, sizeof(int));
                        for (int i = 0; i < k; i++) {
                                // printf("%d ", buff[i]);
                                res0[i] = buff[i];
                        }
                        // printf("\n");
                        (*res)[*returnSize] = res0;
                        (*returnSize)++;

                } else {
                        return;
                }
        } else {
                ;
        }
        int min = idx == 0 ? 1 : buff[idx - 1] + 1;
        for (int i = min; i < 10; i++) {
                if (s + i <= n) {
                        buff[idx] = i;
                        dfs(idx + 1, k, s + i, n, res, returnSize);
                } else {
                        break;
                }
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes) {
        for (int i = 0; i < 10; i++) {
                buff[i] = 0;
        }
        int **res = (int **)calloc(0xff, sizeof(int *));
        *returnSize = 0;
        dfs(0, k, 0, n, &res, returnSize);

        for (int i = 0; i < *returnSize; i++) {
                (*returnColumnSizes)[i] = k;
        }
        return res;
}

int main() { return 0; }