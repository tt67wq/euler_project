/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-27
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

int lengthOfLIS(int *nums, int numsSize) {
        int ans = 0;

        // dp[i] -> 长度为i+1的序列arrays, min(array[-1])
        // dp为递增序列
        int *dp = (int *)calloc(numsSize + 1, sizeof(int));

        for (int i = 0; i < numsSize; i++) {
#ifdef DEBUG
                for (int i = 0; i < numsSize + 1; i++) {
                        printf("%d ", dp[i]);
                }
                printf("\n");
#endif
                // bin-search
                int head = 0, tail = ans;
                while (head < tail) {
                        int mid = (tail + head) / 2;
                        if (dp[mid] < nums[i]) {
                                head = mid + 1;
                        } else {
                                tail = mid;
                        }
                }
                dp[head] = nums[i];
                if (head == ans) {
                        ans++;
                }
        }
        free(dp);
        return ans;
}

int main() {
        int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
        printf("%d\n", lengthOfLIS(nums, 8));
        return 0;
}
