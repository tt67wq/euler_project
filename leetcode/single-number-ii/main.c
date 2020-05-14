/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-14
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

int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}

int singleNumber(int *nums, int numsSize) {
        // sort
        qsort(nums, numsSize, sizeof(int), cmpfunc);

#ifdef DEBUG
        for (int i = 0; i < numsSize; i++) {
                printf("%d ", nums[i]);
        }
        printf("\n");
#endif

        for (int i = 0; i + 2 < numsSize; i += 3) {
                if (nums[i] == nums[i + 1] && nums[i] == nums[i + 2]) {
                        //
                } else {
                        return nums[i];
                }
        }
        return nums[numsSize - 1];
}

int main() {
        int nums[] = {43,          16,         45,          89,          45,
                      -2147483648, 45,         2147483646,  -2147483647, -2147483648,
                      43,          2147483647, -2147483646, -2147483648, 89,
                      -2147483646, 89,         -2147483646, -2147483647, 2147483646,
                      -2147483647, 16,         16,          2147483646,  43};

        printf("%d\n", singleNumber(nums, 25));

        return 0;
}
