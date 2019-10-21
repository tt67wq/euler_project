/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-21
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define UP 0
#define DOWN 1

int zigzag(int *nums, int numSize, int index, int flag) {
        int d;
        if (index == numSize - 1)
                return 0;
        if (flag == UP) {
                if (nums[index] < nums[index + 1]) {
                        return zigzag(nums, numSize, index + 1, DOWN);
                } else {
                        d = nums[index] + 1 - nums[index + 1];
                        nums[index + 1] += d;
                        return d + zigzag(nums, numSize, index + 1, DOWN);
                }
        } else {
        }
}

int movesToMakeZigzag(int *nums, int numsSize) {}

int main() { return 0; }
