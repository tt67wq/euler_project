/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-15
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int firstMissingPositive(int *nums, int numsSize) {
        int *vis, m, i;

        m = 0;
        for (i = 0; i < numsSize; i++) {
                if (nums[i] > m && nums[i] <= numsSize)
                        m = nums[i];
        }
        vis = (int *)calloc(m + 1, sizeof(int));

        for (i = 0; i < numsSize; i++) {
                if (nums[i] > 0 && nums[i] <= numsSize)
                        vis[nums[i]] = 1;
        }
        for (i = 1; i <= m; i++) {
                if (vis[i] == 0)
                        break;
        }

        free(vis);

        if (i < m)
                return i;
        return i;
}

int main() {
        int nums[] = {7, 8, 0};
        printf("%d\n", firstMissingPositive(nums, 3));
        return 0;
}
