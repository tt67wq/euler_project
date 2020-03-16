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

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

int get_next(int *nums, int i, int l) {
        int x = i + nums[i];

        if (x > l) {
                return x % l;
        }
        if (x < 0) {
                return l + x;
        }
        return x;
}

bool circularArrayLoop(int *nums, int numsSize) {
        int l = LENGTH(nums);
        for (int i = 0; i < l; i++) {
                int num = nums[i];
                if (num == 0) {
                        continue;
                }
                int slow = i;                    // slow ptr
                int fast = get_next(nums, i, l); // fast ptr

                // make sure in same direction
                while (nums[slow] * nums[fast] > 0 && nums[slow] * nums[get_next(nums, fast, l)]) {
                        if (slow == fast) {
                                // fast ptr meet slow ptr
                                if (slow == get_next(nums, slow, l)) {
                                        // get ride of circle of 1
                                        break;
                                } else {
                                        // has circle
                                        return true;
                                }
                        }
                        slow = get_next(nums, slow, l);
                        fast = get_next(nums, get_next(nums, fast, l), l);
                }
        }
        return false;
}

int main() {
        int nums[] = {2, -1, 1, 2, 2};
        printf("%d\n", circularArrayLoop(nums, 5));
        return 0;
}
