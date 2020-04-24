/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-24
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
#define ABS(x) ((x) > 0 ? (x) : -(x))

int sums(int *nums, int numsSize) {
        int sum = 0;
        for (int i = 0; i < numsSize; i++) {
                sum += nums[i];
        }
        return sum;
}

int findTargetSumWays(int *nums, int numsSize, int S) {
        // dp[i][j] = nums[i:-1]组成j or -j的组合数量
        // ans = dp[0][S]/2 if S != 0;

        S = ABS(S);
        int sum = sums(nums, numsSize);
        if (S > sum) {
                return 0;
        }

        sum++;

        int **dp = (int **)calloc(numsSize + 1, sizeof(int *));
        for (int i = 0; i < numsSize + 1; i++) {
                dp[i] = (int *)calloc(sum, sizeof(int));
        }

        dp[numsSize][0] = 1;

        for (int i = numsSize; i > 0; i--) {
                for (int j = 0; j < sum; j++) {
                        if (dp[i][j] > 0) {
                                int num = nums[i - 1];
                                dp[i - 1][j + num] += dp[i][j];
                                dp[i - 1][ABS(j - num)] += dp[i][j];
                        }
                }
        }
#ifdef DEBUG
        for (int i = 0; i < numsSize + 1; i++) {
                for (int j = 0; j < sum; j++) {
                        printf("%d ", dp[i][j]);
                }
                printf("\n");
        }
#endif

        int ans = dp[0][S];
        for (int i = 0; i < numsSize + 1; i++) {
                free(dp[i]);
        }
        free(dp);

        return S == 0 ? ans : ans >> 1;
}

int main() {
        int nums[] = {1, 2, 1};
        printf("%d\n", findTargetSumWays(nums, 3, 0));
        return 0;
}
