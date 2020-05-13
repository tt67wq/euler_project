/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-13
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

int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int minMoves2(int *nums, int numsSize) {

        // sort
        qsort(nums, numsSize, sizeof(int), cmpfunc);

        // middle num
        int m;
        if (numsSize & 1) {
                m = nums[numsSize >> 1];
        } else {
                m = (nums[(numsSize >> 1) - 1] + nums[numsSize >> 1]) >> 1;
        }

        int ans = 0;
        for (int i = 0; i < numsSize; i++) {
                int d = nums[i] > m ? nums[i] - m : m - nums[i];
                ans += d;
        }

        return ans;
}

int main() {
        int nums[] = {1, 2, 3};
        printf("%d\n", minMoves2(nums, 3));
        return 0;
}
