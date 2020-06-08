/*
 * =====================================================================================
 *
 *       Filename:  main1.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-08
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void merge(int *A, int ASize, int m, int *B, int BSize, int n) {
        int index = m + n - 1;
        int i = m - 1;
        int j = n - 1;

        while (i >= 0 && j >= 0 && index >= 0) {
                if (A[i] > B[j]) {
                        A[index--] = A[i--];
                } else {
                        A[index--] = B[j--];
                }
        }

        while (i >= 0 && index >= 0) {
                A[index--] = A[i--];
        }

        while (j >= 0 && index >= 0) {
                A[index--] = B[j--];
        }
}

int main() {
        int A[] = {1, 2, 3, 0, 0, 0};
        int B[] = {2, 5, 6};

        merge(A, sizeof(int), 3, B, sizeof(int), 3);
        for (int i = 0; i < 6; i++) {
                printf("%d ", A[i]);
        }
        printf("\n");
        return 0;
}
