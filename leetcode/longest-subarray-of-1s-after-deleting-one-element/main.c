/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-11
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
#define MAX(a, b) (a) > (b) ? (a) : (b)

int longestSubarray(int *nums, int numsSize) {
        int *pre, *suf;

        pre = (int *)calloc(numsSize, sizeof(int));
        suf = (int *)calloc(numsSize, sizeof(int));

        pre[0] = nums[0];
        suf[numsSize - 1] = nums[numsSize - 1];

        for (int i = 1; i < numsSize; i++) {
                pre[i] = nums[i] ? pre[i - 1] + 1 : 0;
        }
        for (int i = numsSize - 2; i >= 0; i--) {
                suf[i] = nums[i] ? suf[i + 1] + 1 : 0;
        }

        // for (int i = 0; i < numsSize; i++) {
        //         printf("%d ", pre[i]);
        // }
        // printf("\n");

        // for (int i = 0; i < numsSize; i++) {
        //         printf("%d ", suf[i]);
        // }
        // printf("\n");

        int ans = 0;
        for (int i = 0; i < numsSize; i++) {
                int preSum = i == 0 ? 0 : pre[i - 1];
                int sufSum = i == numsSize - 1 ? 0 : suf[i + 1];
                ans = MAX(ans, preSum + sufSum);
        }

        free(pre);
        free(suf);
        return ans;
}

int main() {
        int nums[] = {1, 1, 0, 1};
        int ans = longestSubarray(nums, 4);
        printf("%d\n", ans);
        return 0;
}
