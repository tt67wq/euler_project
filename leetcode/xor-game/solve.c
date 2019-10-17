/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* https://leetcode-cn.com/problems/chalkboard-xor-game/ */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool xorGame(int *nums, int numsSize) {
        int i, a = 0;
        for (i = 0; i < numsSize; i++)
                a ^= nums[i];

        if (a == 0)
                return true;
        else
                return numsSize % 2 == 0;
}

int main() { return 0; }
