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

void display(int *array) {
        int i;
        for (i = 0; i < BUFSIZ; i++)
                if (array[i])
                        printf("%-3d", array[i]);

        printf("\n");
}

int main() {
        int n;
        int array[BUFSIZ] = {12, 85, 25, 16, 34, 23, 49, 95, 17, 61};
        quick_sort(array, 0, 9);
        display(array);

        return 0;
}
