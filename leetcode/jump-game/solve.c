/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-17
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
#include <string.h>

bool dfs(int *nums, int numsSize, int cur, int *vis) {
        if (cur == numsSize - 1) {
                return true;
        }
        if (vis[cur] == 1) {
                return true;
        }
        if (vis[cur] == -1) {
                return false;
        }

        int m = nums[cur];
        bool tmp = false;
        for (int i = cur + 1; i <= cur + m && i < numsSize; i++) {
                tmp = tmp || dfs(nums, numsSize, i, vis);
        }

        vis[cur] = tmp ? 1 : -1;

        return tmp;
}

bool canJump(int *nums, int numsSize) {
        int l = numsSize * sizeof(int);
        int *vis = (int *)malloc(l);
        bzero(vis, l);
        return dfs(nums, numsSize, 0, vis);
}

int main() { return 0; }
