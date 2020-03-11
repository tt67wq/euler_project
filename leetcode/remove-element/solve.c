/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-11
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
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
}

int removeElement(int *nums, int numsSize, int val) {
        int ans = numsSize;
        for (int i = 0; i < numsSize; i++) {
                if (nums[i] == val) {
                        ans--;
                }
        }

        for (int i = 0; i < numsSize - 1; i++) {
                if (nums[i] == val) {
                        int j = i + 1;
                        while (j < numsSize && nums[j] == val) {
                                j++;
                        }
                        if (j < numsSize)
                                swap(nums, i, j);
                }
        }

        return ans;
}

int main() {
        int nums[] = {0, 1, 2, 2, 3, 0, 4, 2};
        int ans = removeElement(nums, 8, 2);
        printf("%d\n", ans);
        for (int i = 0; i < ans; i++) {
                printf("%d ", nums[i]);
        }
        printf("\n");
        return 0;
}
