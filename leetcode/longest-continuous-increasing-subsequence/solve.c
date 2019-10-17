/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
 */
#include <stdio.h>
#include <stdlib.h>

int findLengthOfLCIS(int *nums, int numsSize) {
        if (numsSize == 0)
                return 0;
        if (numsSize == 1)
                return 1;
        int i, j;
        int m = 0;
        i = 0;
        j = i + 1;
        while (j < numsSize) {
                if (nums[j] > nums[j - 1]) {
                        j += 1;
                } else {
                        if (j - i > m) {
                                m = j - i;
                        }
                        i = j;
                        j = i + 1;
                }
        }
        if (j - i > m) {
                m = j - i;
        }
        return m;
}

int main() { return 0; }
