/*
 * =====================================================================================
 *
 *       Filename:  quick_sort.c
 *
 *    Description:  快排
 *
 *        Version:  1.0
 *        Created:  2019-07-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); } */
int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}

int compare(void *a, void *b) {
        printf("comparing %d and %d\n", *(int *)a, *(int *)b);
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
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

int main() {
        // 1, 5, 2, 3, 7
        int a[] = {0, 2};
        int b[] = {2, 3};
        int c[] = {4, 4};
        int d[] = {0, 1};
        int e[] = {5, 7};
        int f[] = {4, 5};
        int g[] = {0, 0};

        int *intervals[] = {a, b, c, d, e, f, g};
        ;
        int (*p)(void *, void *) = compare;
        quick_sort((void **)intervals, 0, 6, p);

        for (int i = 0; i < 7; i++) {
                printf("[%d, %d] ", intervals[i][0], intervals[i][1]);
        }
        printf("\n");

        return 0;
}
