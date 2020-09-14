/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-14
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

bool search(int *nums, int numsSize, int target) {
        if (numsSize == 0) {
                return false;
        }
        if (numsSize == 1) {
                return nums[0] == target;
        }
        int start = 0, end = numsSize - 1;
        int mid;
        while (start <= end) {
                mid = start + (end - start) / 2;
                if (nums[mid] == target) {
                        return true;
                }
                if (nums[start] == nums[mid]) {
                        start++;
                        continue;
                }
                if (nums[start] < nums[mid]) {
                        if (nums[mid] > target && nums[start] <= target) {
                                end = mid - 1;
                        } else {
                                start = mid + 1;
                        }
                } else {
                        if (nums[mid] < target && nums[end] >= target) {
                                start = mid + 1;
                        } else {
                                end = mid - 1;
                        }
                }
        }
        return false;
}

int main() {
        int nums[] = {1, 3};
        bool flag = search(nums, 2, 3);
        printf("%d\n", flag);
        return 0;
}