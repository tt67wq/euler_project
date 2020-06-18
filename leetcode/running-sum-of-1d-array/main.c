/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *runningSum(int *nums, int numsSize, int *returnSize) {
        int *res = (int *)calloc(numsSize, sizeof(int));
        int acc = 0;
        for (int i = 0; i < numsSize; i++) {
                acc += nums[i];
                res[i] = acc;
        }
        (*returnSize) = numsSize;
        return res;
}

int main() {
        int nums[] = {1, 2, 3, 4};
        int size;
        int *ans = runningSum(nums, 4, &size);
        for (int i = 0; i < size; i++) {
                printf("%d ", ans[i]);
        }
        printf("\n");
        free(ans);
        return 0;
}