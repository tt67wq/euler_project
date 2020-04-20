/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-20
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

#define MAX 1000
#define DEBUG

void swap(int *a, int *b) {
        int tmp;
        tmp = *a;
        *a = *b;
        *b = tmp;
}

void quick_sort(int *nums, int begin, int end) {
        int i, j;
        if (begin < end) {
                i = begin + 1;
                j = end;
                while (i < j) {
                        if (nums[i] > nums[begin]) {
                                swap(&nums[i], &nums[j]);
                                j--;
                        } else {
                                i++;
                        }
                }
                if (nums[i] >= nums[begin]) {
                        i--;
                }

                swap(&nums[i], &nums[begin]);
                quick_sort(nums, begin, i);
                quick_sort(nums, j, end);
        }
}

void backtrack(int *nums, int numsSize, int idx, int *buff, int **ptr, int *size) {

        if (numsSize == 0) {
#ifdef DEBUG
                for (int i = 0; i < idx; i++) {
                        printf("%d ", buff[i]);
                }
                printf("\n");
#endif

                int *temp = (int *)malloc(sizeof(int) * idx);
                memcpy(temp, buff, sizeof(int) * idx);
                ptr[(*size)++] = temp;
                return;
        }

        for (int i = 0; i < numsSize; i++) {
                if (i > 0 && nums[i] == nums[i - 1]) {
                        continue;
                }
                buff[idx] = nums[i];

                // kick out S[i]
                int *nums0 = (int *)calloc(numsSize, sizeof(int));
                int k = 0;

                for (int j = 0; j < numsSize; j++) {
                        if (j != i) {
                                nums0[k++] = nums[j];
                        }
                }

                backtrack(nums0, k, idx + 1, buff, ptr, size);
                buff[idx] = 0;
                free(nums0);
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permuteUnique(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {

        // sort
        quick_sort(nums, 0, numsSize - 1);

        int *buff = (int *)malloc(sizeof(int) * numsSize);
        int size = 0;
        int **result = (int **)calloc(MAX, sizeof(int *));

        backtrack(nums, numsSize, 0, buff, result, &size);
        free(buff);
        *returnSize = size;
        for (int i = 0; i < size; i++) {
                (*returnColumnSizes)[i] = numsSize;
        }
        return result;
}

int main() {
        int nums[] = {1, 1, 2, 2};
        int *buff = (int *)malloc(sizeof(int) * 4);
        int size = 0;
        int **result = (int **)calloc(MAX, sizeof(int *));

        backtrack(nums, 4, 0, buff, result, &size);
        free(buff);

        printf("----------------\n");
        printf("size => %d\n", size);

        for (int i = 0; i < size; i++) {
                for (int j = 0; j < 4; j++) {
                        printf("%d ", result[i][j]);
                }
                printf("\n");
                free(result[i]);
        }
        free(result);

        printf("finished\n");

        return 0;
}
