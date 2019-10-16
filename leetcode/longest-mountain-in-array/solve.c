/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int longestMountain(int *A, int ASize) {
        if (ASize < 3) {
                return 0;
        }

        int i, x, y, longest = 0;
        for (i = 1; i < ASize - 1; i++) {
                // peak?
                if (A[i] > A[i - 1] && A[i] > A[i + 1]) {
                        x = i - 1;
                        while (x > 0) {
                                if (A[x] > A[x - 1])
                                        x--;
                                else
                                        break;
                        }
                        y = i + 1;
                        while (y < ASize - 1) {
                                if (A[y] > A[y + 1])
                                        y++;
                                else
                                        break;
                        }
                        if (y - x + 1 > longest)
                                longest = y - x + 1;
                }
        }
        return longest;
}

int main() {
        int nums[] = {2, 1, 4, 7, 3, 2, 5};
        printf("%d\n", longestMountain(nums, 7));
        return 0;
}
