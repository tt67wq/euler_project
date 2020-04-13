/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int minSteps(int *a, int *b) {
        int dx = a[0] - b[0];
        int dy = a[1] - b[1];

        dx = dx > 0 ? dx : -dx;
        dy = dy > 0 ? dy : -dy;

        return dx > dy ? dx : dy;
}

int minTimeToVisitAllPoints(int **points, int pointsSize, int *pointsColSize) {
        int ans = 0;
        for (int i = 1; i < pointsSize; i++) {
                ans += minSteps(points[i], points[i - 1]);
        }
        return ans;
}

int main() { return 0; }
