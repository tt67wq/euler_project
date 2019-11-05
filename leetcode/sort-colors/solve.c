/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-05
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *nums, int i, int j) {
        int tmp;
        tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
}

void sortColors(int *nums, int numsSize) {
        int i, r1, r2;

        r1 = -1;
        r2 = -1;

        for (i = 0; i < numsSize; i++) {
                if (nums[i] < 2) {
                        r2++;
                        swap(nums, i, r2);
                        if (nums[r2] < 1) {
                                r1++;
                                swap(nums, r1, r2);
                        }
                }
        }
}

int main() {
        int i;
        int nums[] = {2, 0, 2, 1, 1, 0};
        sortColors(nums, 6);
        for (i = 0; i < 6; i++)
                printf("%d ", nums[i]);

        return 0;
}
