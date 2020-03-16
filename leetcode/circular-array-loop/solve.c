/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-16
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

int get_next(int *nums, int i, int l) {
        int x = i + nums[i];

        while (x >= l) {
                x = x % l;
        }
        while (x < 0) {
                x = l + x;
        }
        return x;
}

bool circularArrayLoop(int *nums, int numsSize) {
        for (int i = 0; i < numsSize; i++) {
                int num = nums[i];
                if (num == 0) {
                        continue;
                }
                int slow = i;                           // slow ptr
                int fast = get_next(nums, i, numsSize); // fast ptr

                printf("slow: %d, fast: %d\n", slow, fast);
                // make sure in same direction
                while (nums[slow] * nums[fast] > 0 &&
                       nums[slow] * nums[get_next(nums, fast, numsSize)] > 0) {
                        printf("   slow: %d, fast: %d\n", slow, fast);
                        if (slow == fast) {
                                // fast ptr meet slow ptr
                                if (slow == get_next(nums, slow, numsSize)) {
                                        // get ride of circle of 1
                                        break;
                                } else {
                                        // has circle

                                        return true;
                                }
                        }
                        slow = get_next(nums, slow, numsSize);
                        fast = get_next(nums, get_next(nums, fast, numsSize), numsSize);
                }
        }
        return false;
}

int main() {
        int nums[] = {-2, -3, -9};
        printf("%d\n", circularArrayLoop(nums, 3));
        return 0;
}
