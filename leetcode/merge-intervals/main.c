/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int compare(void *a, void *b) {
        int *x = (int *)a;
        int *y = (int *)b;
        if (*x > *y) {
                return 1;
        } else if (*x < *y) {
                return -1;
        } else {
                return 0;
        }
}

void swap(void **a, void **b) {
        void *temp;

        temp = *a;
        *a = *b;
        *b = temp;

        return;
}

void quick_sort(void **array, int begin, int end, int (*cmp)(void *, void *)) {
        int i, j;
        if (begin < end) {
                i = begin + 1;
                j = end;
                while (i < j) {
                        if (cmp(array[i], array[begin]) > 0) {
                                swap(&array[i], &array[j]);
                                j--;
                        } else {
                                i++;
                        }
                }

                if (cmp(array[i], array[begin]) >= 0)
                        i--;

                swap(&array[begin], &array[i]);
                quick_sort(array, begin, i, cmp);
                quick_sort(array, j, end, cmp);
        }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize,
            int **returnColumnSizes) {
        if (intervalsSize == 0) {
                *returnSize = 0;
                *returnColumnSizes = NULL;
                return NULL;
        }

        // sort
        int (*p)(void *, void *) = compare;
        quick_sort((void **)intervals, 0, intervalsSize - 1, p);

        // sort result
        /* for (int i = 0; i < intervalsSize; i++) { */
        /*         printf("[%d, %d] ", intervals[i][0], intervals[i][1]); */
        /* } */
        /* printf("\n"); */

        int **ans = (int **)malloc(sizeof(int *) * intervalsSize);

        int last = 0;
        ans[0] = intervals[0];
        for (int i = 1; i < intervalsSize; i++) {
                /* printf("last => [%d, %d], intervals[%d] => [%d, %d]\n", ans[last][0],
                 * ans[last][1], */
                /*              i, intervals[i][0], intervals[i][1]); */
                if (ans[last][1] >= intervals[i][0]) {
                        ans[last][1] =
                            ans[last][1] > intervals[i][1] ? ans[last][1] : intervals[i][1];
                } else {
                        last++;
                        ans[last] = intervals[i];
                }
        }
        *returnSize = last + 1;
        *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
        for (int i = 0; i < *returnSize; i++) {
                (*returnColumnSizes)[i] = 2;
        }
        return ans;
}

int main() {
        //[[0,2],[2,3],[4,4],[0,1],[5,7],[4,5],[0,0]]
        int a[] = {0, 2};
        int b[] = {2, 3};
        int c[] = {4, 4};
        int d[] = {0, 1};
        int e[] = {5, 7};
        int f[] = {4, 5};
        int g[] = {0, 0};

        int *intervals[] = {a, b, c, d, e, f, g};
        int returnSize = 0;
        int *returnColumnSizes;

        int **ans = merge(intervals, 7, NULL, &returnSize, &returnColumnSizes);

        free(returnColumnSizes);
        for (int i = 0; i < returnSize; i++) {
                printf("[%d, %d] ", ans[i][0], ans[i][1]);
        }
        printf("\n");

        free(ans);

        return 0;
}
