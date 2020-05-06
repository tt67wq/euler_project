/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-05-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
int K = 0;
int SIZE = 0;
int TARGET = 0;

int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

bool dfs(int *nums, int *vis, int acc, int hits, int idx) {
        if (idx >= SIZE) {
                return false;
        }

        if (hits == K) {
                return true;
        }

        for (int i = idx; i < SIZE; i++) {
                if (vis[i] > 0) {
                        continue;
                }

                if (acc + nums[i] == TARGET) {
                        vis[i] = 1;
                        if (dfs(nums, vis, 0, hits + 1, 0))
                                return true;
                        vis[i] = 0;
                        for (; i + 1 < SIZE && nums[i] == nums[i + 1]; i++)
                                ;
                } else if (acc + nums[i] < TARGET) {
                        vis[i] = 1;
                        if (dfs(nums, vis, acc + nums[i], hits, i + 1))
                                return true;
                        vis[i] = 0;
                        for (; i + 1 < SIZE && nums[i] == nums[i + 1]; i++)
                                ;
                } else {
                        break;
                }
        }
        return false;
}

bool canPartitionKSubsets(int *nums, int numsSize, int k) {
        if (numsSize == 0 || k == 0) {
                return false;
        }
        int sum = 0, max1 = INT_MIN;
        for (int i = 0; i < numsSize; i++) {
                max1 = max1 > nums[i] ? max1 : nums[i];
                sum += nums[i];
        }
        if (sum % k != 0 || max1 > (sum / k)) {
                return false;
        }

        qsort(nums, numsSize, sizeof(int), cmpfunc);

#ifdef DEBUG
        for (int i = 0; i < numsSize; i++) {
                printf("%d ", nums[i]);
        }
        printf("\n");
#endif
        int *vis = (int *)calloc(numsSize, sizeof(int));

        K = k;
        SIZE = numsSize;
        TARGET = sum / k;
        bool ans = dfs(nums, vis, 0, 0, 0);

        free(vis);

        return ans;
}

int main() {
        /* [] */
        /* 6 */

        int nums[] = {7628, 3147, 7137, 2578, 7742, 2746, 4264, 7704,
                      9532, 9679, 8963, 3223, 2133, 7792, 5911, 3979};

        printf("%d\n", canPartitionKSubsets(nums, 16, 6));

        int nums2[] = {4, 3, 2, 3, 5, 2, 1};
        printf("%d\n", canPartitionKSubsets(nums2, 7, 4));
        return 0;
}
