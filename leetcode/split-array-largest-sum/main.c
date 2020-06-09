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
        long mx = 0;
        long sum = 0;

        for (int i = 0; i < numsSize; i++) {
                if (nums[i] > mx) {
                        mx = (long)nums[i];
                }
                sum += (long)nums[i];
        }

        if (numsSize == m) {
                return (int)mx;
        }

        long lo = mx;
        long hi = sum;

        while (lo < hi) {
                long mid = (lo + hi) >> 1;
                long tmp = 0;
                int cnt = 1;

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
        return (int)lo;
}

int main() {
        int nums[] = {1, 2147483647};
        printf("%d\n", splitArray(nums, 2, 2));
        return 0;
}
