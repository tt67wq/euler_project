/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-17
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
#include <string.h>

#define DEBUG

int CACHE[501][501];

int dp(int *nums1, int left, int right) {

        // cache
        if (CACHE[left][right] > 0) {
                return CACHE[left][right];
        }
        if (left + 1 == right) {
                return 0;
        }

        int max = INT_MIN;
        for (int i = left + 1; i < right; i++) {
                int lm = dp(nums1, left, i);
                int rm = dp(nums1, i, right);
                int tmp = nums1[left] * nums1[i] * nums1[right] + lm + rm;
                max = tmp > max ? tmp : max;
        }
        CACHE[left][right] = max;
        return max;
}

int maxCoins(int *nums, int numsSize) {
        int *nums1 = (int *)calloc(numsSize + 2, sizeof(int));
        for (int i = 0; i < numsSize; i++) {
                nums1[i + 1] = nums[i];
        }
        nums1[0] = 1;
        nums1[numsSize + 1] = 1;

        for (int i = 0; i < 500; i++) {
                memset(CACHE[i], 0, sizeof(int) * 500);
        }

        int ans = dp(nums1, 0, numsSize + 1);
        free(nums1);
        return ans;
}

int main() {
        int nums[] = {3, 1, 5, 8};
        printf("%d\n", maxCoins(nums, 4));
        return 0;
}