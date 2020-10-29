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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// check if [0, k] overlapping decreasing area
bool check(int *arr, int size, int k) {
        if (k == size - 1)
                return true;
        int lo = 0, hi = size - 1;
        while (lo < hi && arr[lo] <= arr[lo + 1])
                ++lo;
        while (hi > lo && arr[hi] >= arr[hi - 1])
                --hi;

        // [0,lo][lo+1,hi-1][hi,size-1]
        if (hi <= k || size - lo - 1 <= k)
                return true;

        if (hi - lo - 1 > k)
                return false;

        for (int i = fmax(0, hi - k - 1); i <= lo && i + k + 1 < size; ++i) {
                if (arr[i] <= arr[i + k + 1])
                        return true;
        }
        return false;
}

int findLengthOfShortestSubarray(int *arr, int arrSize) {
        int lo = 0, hi = arrSize - 1;
        while (lo < hi) {
                int mid = (lo + hi) >> 1;
                if (check(arr, arrSize, mid)) {
                        hi = mid;
                } else {
                        lo = mid + 1;
                }
        }
        return lo;
}

int main() { return 0; }