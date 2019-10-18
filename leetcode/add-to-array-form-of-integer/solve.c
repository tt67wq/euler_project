/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void reverse(int *A, int Size) {
        int i, tmp;
        for (i = 0; i < Size / 2; i++) {
                tmp = A[i];
                A[i] = A[Size - 1 - i];
                A[Size - 1 - i] = tmp;
        }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *addToArrayForm(int *A, int ASize, int K, int *returnSize) {
        int i = 0, j = 0;

        int *B;
        B = (int *)calloc(ASize, sizeof(int));

        for (i = 0; i < ASize; i++)
                B[i] = A[i];

        reverse(B, ASize);

        i = 0;
        *returnSize = ASize;
        while (j != 0 || i < ASize || K != 0) {
                if (i >= ASize) {
                        B = (int *)realloc(B, (i + 1) * sizeof(int));
                        *returnSize += 1;
                }

                B[i] += K % 10;
                B[i] += j;
                if (B[i] > 9) {
                        B[i] %= 10;
                        j = 1;
                } else {
                        j = 0;
                }
                K /= 10;
                i++;
        }
        reverse(B, *returnSize);
        return B;
}

int main() {
        int A[] = {2, 1, 5};
        int i, returnSize;
        int *B;

        B = addToArrayForm(A, 3, 806, &returnSize);
        for (i = 0; i < returnSize; i++) {
                printf("%d ", B[i]);
        }
        return 0;
}
