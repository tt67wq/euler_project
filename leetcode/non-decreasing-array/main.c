/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-08
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

#define ARRAY_LEN(a) (sizeof((a)) / sizeof((a)[0]))

bool checkPossibility(int *nums, int numsSize) {
        int i, cnt, x, y;

        cnt = 0;
        for (i = 0; i < numsSize - 1; i++) {
                x = nums[i], y = nums[i + 1];
                if (x > y) {
                        cnt++;
                        if (cnt > 1) {
                                return false;
                        }
                        if (i > 0 && y < nums[i - 1]) {
                                nums[i + 1] = x;
                        }
                }
        }
        return true;
}

int main() {
        int nums[] = {4, 2, 3};
        printf("%d\n", checkPossibility(nums, ARRAY_LEN(nums)));
        return 0;
}