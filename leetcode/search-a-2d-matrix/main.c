/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-21
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

#define DEBUG

int binarySearch(int a[], int n, int key) {
        int low = 0;
        int high = n - 1;
        while (low <= high) {
                int mid = low + (high - low) / 2;
                int midVal = a[mid];
                if (midVal < key)
                        low = mid + 1;
                else if (midVal > key)
                        high = mid - 1;
                else
                        return mid;
        }
        return -1;
}

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target) {
        bool res = false;
        for (int i = 0; i < matrixSize; i++) {
                if (matrixColSize[i] > 0 && target >= matrix[i][0] &&
                    target <= matrix[i][matrixColSize[i] - 1]) {
                        if (binarySearch(matrix[i], matrixColSize[i], target) >= 0) {
                                res = true;
                        }
                        break;
                }
        }
        return res;
}

int main() { return 0; }