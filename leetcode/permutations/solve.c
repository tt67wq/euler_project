/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
        int s = 1;
        while (n > 0) {
                s *= n;
                n--;
        }
        return s;
}

void perm(int deep, int n, int *nums, int *res, int *vis, int *idx, int **ans) {
        int i;
        if (deep > n)
                return;

        if (deep == n) {
                for (i = 0; i < n; i++) {
                        ans[*idx][i] = res[i];
                }
                (*idx)++;
                return;
        }

        for (i = 0; i < n; i++) {
                if (vis[i] == 0) {
                        vis[i] = 1;
                        res[deep] = nums[i];
                        perm(deep + 1, n, nums, res, vis, idx, ans);
                        vis[i] = 0;
                }
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
        if (numsSize == 0) {
                *returnSize = 0;
                returnColumnSizes = NULL;
                return NULL;
        }
        int i, **ans, *res, *vis, idx;

        if (numsSize == 1) {
                *returnSize = 1;
                returnColumnSizes[0] = (int *)calloc(1, sizeof(int));
                returnColumnSizes[0][0] = 1;
                ans = (int **)calloc(1, sizeof(int *));
                ans[0] = (int *)calloc(1, sizeof(int));
                ans[0][0] = nums[0];

                return ans;
        }

        *returnSize = factorial(numsSize);
        returnColumnSizes[0] = (int *)calloc(*returnSize, sizeof(int));
        ans = (int **)calloc(*returnSize, sizeof(int *));

        for (i = 0; i < *returnSize; i++) {
                returnColumnSizes[0][i] = numsSize;
                ans[i] = (int *)calloc(numsSize, sizeof(int));
        }

        res = (int *)calloc(numsSize, sizeof(int));
        vis = (int *)calloc(numsSize, sizeof(int));
        idx = 0;
        perm(0, numsSize, nums, res, vis, &idx, ans);
        free(res);
        free(vis);

        return ans;
}

int main() {
        int nums[3] = {1, 2, 3};
        int i, j, returnSize, **ans, **returnColumnSizes;
        returnColumnSizes = (int **)calloc(1, sizeof(int *));

        ans = permute(nums, 3, &returnSize, returnColumnSizes);
        for (i = 0; i < returnSize; i++) {
                for (j = 0; j < returnColumnSizes[0][i]; j++) {
                        printf("%d ", ans[i][j]);
                }
                printf("\n");
        }

        // free returnColumnSizes
        free(returnColumnSizes[0]);
        free(returnColumnSizes);

        // free ans
        for (i = 0; i < returnSize; i++)
                free(ans[i]);
        free(ans);

        return 0;
}
