/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
        int temp;

        temp = *a;
        *a = *b;
        *b = temp;

        return;
}

void quick_sort(int *array, int begin, int end) {
        int i, j;
        if (begin < end) {
                i = begin + 1;
                j = end;
                while (i < j) {
                        if (array[i] > array[begin]) {
                                swap(&array[i], &array[j]);
                                j--;
                        } else {
                                i++;
                        }
                }

                if (array[i] >= array[begin])
                        i--;

                swap(&array[begin], &array[i]);
                quick_sort(array, begin, i);
                quick_sort(array, j, end);
        }
}

int findUnsortedSubarray(int *nums, int numsSize) {
        int *wuq, i, j, lf, rf;

        wuq = (int *)calloc(numsSize, sizeof(int));

        memcpy(wuq, nums, sizeof(int) * numsSize);

        quick_sort(nums, 0, numsSize - 1);

        // compare
        i = 0;
        j = numsSize - 1;
        lf = 0;
        rf = 0;
        while (i < j && (lf == 0 || rf == 0)) {
                if (nums[i] == wuq[i]) {
                        i++;
                } else {
                        lf = 1;
                }
                if (nums[j] == wuq[j]) {
                        j--;
                } else {
                        rf = 1;
                }
        }
        if (i == j)
                return 0;
        return j - i + 1;
}

int main() {
        int nums[] = {2, 6, 4, 8, 10, 9, 15};
        printf("%d\n", findUnsortedSubarray(nums, 7));
        return 0;
}
