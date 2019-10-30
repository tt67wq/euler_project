/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-30
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int minSwap(int *A, int ASize, int *B, int BSize) {
        int cost[2];
        int i, t;

        cost[0] = 0; // not swap
        cost[1] = 1; // swap

        for (i = 1; i < ASize; i++) {
                if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
                        if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
                                cost[0] = cost[0] > cost[1] ? cost[1] : cost[0];
                                cost[1] = 1 + (cost[0] > cost[1] ? cost[1] : cost[0]);
                        } else {
                                cost[1] += 1;
                        }
                } else {
                        t = cost[0];
                        cost[0] = cost[1];
                        cost[1] = t + 1;
                }
        }
        return cost[0] > cost[1] ? cost[1] : cost[0];
}

int main() {
        int A[4] = {1, 3, 5, 4};
        int B[4] = {1, 2, 3, 7};
        printf("%d\n", minSwap(A, 4, B, 4));
        return 0;
}
