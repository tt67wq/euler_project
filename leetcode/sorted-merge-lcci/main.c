/*
 * =====================================================================================
 *
 *       Filename:  main.c
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

/* int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); } */
int cmpfunc(const void *a, const void *b) {
        if (*(int *)a > *(int *)b) {
                return 1;
        } else if (*(int *)a < *(int *)b) {
                return -1;
        }
        return 0;
}

void merge(int *A, int ASize, int m, int *B, int BSize, int n) {
        int i = n;
        while (i--) {
                A[m + i] = B[i];
        }
        qsort(A, (m + n), sizeof(int), cmpfunc);
}

int main() { return 0; }
