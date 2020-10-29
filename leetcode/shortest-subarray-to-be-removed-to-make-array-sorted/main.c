/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-10-29
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (a) > (b) ? (b) : (a)

int findLengthOfShortestSubarray(int *arr, int arrSize) {
        int left = 0;

        while (left + 1 < arrSize && arr[left] <= arr[left + 1]) {
                ++left;
        }

        if (left == arrSize - 1) {
                return 0;
        }

        int right = arrSize - 1;
        while (right > 0 && arr[right - 1] <= arr[right]) {
                --right;
        }

        int res = MIN(arrSize - left - 1, right);

        int i = 0, j = right;

        while (i <= left && j <= arrSize - 1) {
                if (arr[i] <= arr[j]) {
                        res = MIN(res, j - i - 1);
                        ++i;
                } else {
                        ++j;
                }
        }
        return res;
}

int main() { return 0; }