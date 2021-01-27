/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-01-27
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

const int MOD = 1e9 + 7;

int waysToSplit(int *nums, int numsSize) {
        int res = 0;
        int prefixSum[100005];
        int tmp = 0;

        for (int i = 0; i < numsSize; i++) {
                tmp += nums[i];
                prefixSum[i + 1] = tmp;
        }

        for (int i = 1; i < numsSize - 1; i++) {
                int left = prefixSum[i];
                int mid, leftMost;
                int l = i + 1, r = numsSize;

                while (r > l) {
                        mid = l + ((r - l) >> 1);
                        if (prefixSum[mid] >= (left << 1)) {
                                r = mid;
                        } else {
                                l = mid + 1;
                        }
                }
                leftMost = r;

                l = i + 1;
                r = numsSize;

                while (r > l) {
                        mid = l + ((r - l) >> 1);
                        if (prefixSum[numsSize] - prefixSum[mid] >= prefixSum[mid] - left) {
                                l = mid + 1;
                        } else {
                                r = mid;
                        }
                }
                if (r > leftMost) {
                        res += (r - leftMost);
                        res %= MOD;
                }
        }
        return res;
}

int main() {
        int nums[] = {1, 1, 1};
        int res = waysToSplit(nums, 3);
        printf("%d\n", res);
        return 0;
}