/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-09
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

int splitArray(int *nums, int numsSize, int m) {
        int mx = 0;
        int sum = 0;

        for (int i = 0; i < numsSize; i++) {
                if (nums[i] > mx) {
                        mx = nums[i];
                }
                sum += nums[i];
        }

        if (numsSize == m) {
                return mx;
        }

        int lo = mx;
        int hi = sum;

        while (lo < hi) {
                int mid = (lo + hi) >> 1;
                int tmp = 0, cnt = 1;

                for (int i = 0; i < numsSize; i++) {
                        tmp += nums[i];
                        if (tmp > mid) {
                                tmp = nums[i];
                                cnt++;
                        }
                }
                if (cnt > m) {
                        lo = mid + 1;
                } else {
                        hi = mid;
                }
        }
        return lo;
}

int main() { return 0; }
