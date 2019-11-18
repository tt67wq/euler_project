/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-18
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

int heightChecker(int *heights, int heightsSize) {
        int *copy, i, ans;

        copy = (int *)calloc(heightsSize, sizeof(int));
        memcpy(copy, heights, sizeof(int) * heightsSize);
        quick_sort(copy, 0, heightsSize - 1);

        ans = 0;
        for (i = 0; i < heightsSize; i++) {
                if (heights[i] != copy[i])
                        ans++;
        }
	free(copy);
        return ans;
}

int main() {
        int heights[] = {1, 1, 4, 2, 1, 3};
        printf("%d\n", heightChecker(heights, 6));
        return 0;
}
