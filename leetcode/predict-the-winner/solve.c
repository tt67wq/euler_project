/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-13
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

bool predict(int *nums, int idx, int left, int right, int s1, int s2) {
        // last one
        if (left == right) {
                if (idx % 2 == 0) {
                        // me
                        if (nums[left] + s1 >= s2)
                                return true;
                        else
                                return false;
                } else {
                        // you
                        if (nums[left] + s2 > s1)
                                return false;
                        else
                                return true;
                }
        }

        if (idx % 2 == 0) {
                // me
                return predict(nums, idx + 1, left + 1, right, s1 + nums[left], s2) || predict(nums, idx + 1, left, right - 1, s1 + nums[right], s2);
        } else {
                // you
                return predict(nums, idx + 1, left + 1, right, s1, s2 + nums[left]) && predict(nums, idx + 1, left, right - 1, s1, s2 + nums[right]);
        }
}

bool PredictTheWinner(int *nums, int numsSize) { return predict(nums, 0, 0, numsSize - 1, 0, 0); }

int main() {
        int nums[] = {1, 5, 2};
        printf("%d\n", PredictTheWinner(nums, 3));
        return 0;
}
