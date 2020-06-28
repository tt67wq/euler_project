/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-23
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

#define DEBUG

int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *arrayRankTransform(int *arr, int arrSize, int *returnSize) {

        if (arrSize == 0) {
                (*returnSize) = 0;
                return NULL;
        }

        int *arr1 = (int *)malloc(arrSize * sizeof(int));
        memcpy(arr1, arr, sizeof(int) * arrSize);

        qsort(arr1, arrSize, sizeof(int), cmpfunc);
        int *seq = (int *)calloc(arrSize, sizeof(int));

        seq[0] = 1;
        for (int i = 1; i < arrSize; i++) {
                if (arr1[i] == arr1[i - 1]) {
                        seq[i] = seq[i - 1];
                } else {
                        seq[i] = seq[i - 1] + 1;
                }
        }

        int *ans = (int *)calloc(arrSize, sizeof(int));

        for (int i = 0; i < arrSize; i++) {
                // bin search
                int left = 0;
                int right = arrSize - 1;
                while (left <= right) {
                        int middle = left + ((right - left) >> 1);
                        if (arr1[middle] > arr[i]) {
                                right = middle - 1;
                        } else if (arr1[middle] < arr[i]) {
                                left = middle + 1;
                        } else {
                                ans[i] = seq[middle];
                                break;
                        }
                }
        }

        free(arr1);
        free(seq);
        (*returnSize) = arrSize;
        return ans;
}

int main() {
        int arr[] = {40, 10, 20, 30};
        int returnSize;
        int *ans = arrayRankTransform(arr, 4, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%d ", ans[i]);
        }
        printf("\n");
        return 0;
}