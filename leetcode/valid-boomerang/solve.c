/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-01-11
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

bool zero_area(int **points) {
        // 设A(x1,y1),B(x2,y2),C(x3,y3)
        // S=(1/2)*(x1y2+x2y3+x3y1-x1y3-x2y1-x3y2)

        int *A, *B, *C;

        A = points[0];
        B = points[1];
        C = points[2];

        return A[0] * B[1] + B[0] * C[1] + C[0] * A[1] - A[0] * C[1] - B[0] * A[1] - C[0] * B[1] == 0;
}

bool isBoomerang(int **points, int pointsSize, int *pointsColSize) { return !zero_area(points); }

int main() { return 0; }
