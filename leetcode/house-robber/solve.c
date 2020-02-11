/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-02-11
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

typedef struct _elem {
        int m;
        bool r;
} elem;

int rob(int *nums, int numsSize) {
        if (numsSize == 0) {
                return 0;
        }
        if (numsSize == 1) {
                return nums[0];
        }
        elem *dp;
        int i, ans;

        dp = (elem *)calloc(numsSize, sizeof(elem));

        dp[0].m = nums[0];
        dp[0].r = true;

        if (nums[1] > nums[0]) {
                dp[1].m = nums[1];
                dp[1].r = true;
        } else {
                dp[1].m = nums[0];
                dp[1].r = false;
        }

        for (i = 2; i < numsSize; i++) {
                if (dp[i - 1].r) {
                        if (dp[i - 2].m + nums[i] > dp[i - 1].m) {
                                dp[i].m = dp[i - 2].m + nums[i];
                                dp[i].r = true;
                        } else {
                                dp[i].m = dp[i - 1].m;
                                dp[i].r = false;
                        }
                } else {
                        dp[i].r = true;
                        dp[i].m = dp[i - 1].m + nums[i];
                }
        }

        ans = dp[numsSize - 1].m;
        free(dp);
        return ans;
}

int main() {
        int nums[] = {2, 7, 9, 3, 1};
        printf("%d\n", rob(nums, 5));
        return 0;
}
