/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortArrayByParity(int *A, int ASize, int *returnSize) {
        int i, j, t;
        i = 0;
        j = ASize - 1;

        while (1) {
                while (i < ASize && A[i] % 2 == 0)
                        i++;
                while (j > 0 && A[j] % 2 == 1)
                        j--;

                if (i + 1 <= j) {
                        t = A[i];
                        A[i] = A[j];
                        A[j] = t;
                        i++;
                        j--;
                } else
                        break;
        }

        *returnSize = ASize;
        return A;
}

int main() { return 0; }
