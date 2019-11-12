/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-11
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool validMountainArray(int *A, int ASize) {
        if (ASize < 3)
                return false;
        int i, j, up, down, ups, downs;

        i = 0;
        j = ASize - 1;
        up = 1;
        down = 1;
        ups = 0;
        downs = 0;

        while (i + 1 < j) {
                if (up == 1 && A[i] < A[i + 1]) {
                        i++;
                        ups++;
                } else {
                        up = 0;
                }

                if (down == 1 && A[j] < A[j - 1]) {
                        j--;
                        downs++;
                } else {
                        down = 0;
                }

                if (up == 0 && down == 0)
                        break;
        }

        if (ups == 0 || downs == 0)
                return false;

        if (i + 1 < j)
                return false;
        else if (i == j)
                return true;
        else if (i + 1 == j)
                return A[i] != A[j];
        else
                return false;
}

int main() {
        int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        printf("%d\n", validMountainArray(A, 10));
        return 0;
}
