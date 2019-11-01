/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
        int i, left = 1, right = 1;
        int *res;

        res = (int *)calloc(numsSize, sizeof(int));

        for (i = 0; i < numsSize; i++)
                res[i] = 1;

        for (i = 0; i < numsSize; i++) {
                res[i] *= left;
                left *= nums[i];

                res[numsSize - 1 - i] *= right;
                right *= nums[numsSize - 1 - i];
        }
        *returnSize = numsSize;
        return res;
}

int main() {
        int nums[4] = {1, 2, 3, 4};
        int *res;
        int i, returnSize;
        res = productExceptSelf(nums, 4, &returnSize);

        for (i = 0; i < 4; i++)
                printf("%d\t", res[i]);
        printf("\n");

        return 0;
}
