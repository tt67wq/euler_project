/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-26
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *distributeCandies(int candies, int num_people, int *returnSize) {
        int *ans, i, j;

        ans = (int *)calloc(num_people, sizeof(int));
        *returnSize = num_people;

        j = 1;
        i = 0;

        while (1) {
                ans[i++] += j;
                candies -= j++;

                if (i == num_people)
                        i = 0;
                if (candies < j) {
                        j = candies;
                        break;
                }
        }
        ans[i] += j;
        return ans;
}

int main() { return 0; }
