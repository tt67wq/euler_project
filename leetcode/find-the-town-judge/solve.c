/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-31
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int findJudge(int N, int **trust, int trustSize, int *trustColSize) {
        int i, **ziq, *ujo;
        ziq = (int **)calloc(N, sizeof(int *));
        for (i = 0; i < N; i++) {
                ziq[i] = (int *)calloc(2, sizeof(int));
        }

        for (i = 0; i < trustSize; i++) {
                ujo = trust[i];
                ziq[ujo[0] - 1][0]++;
                ziq[ujo[1] - 1][1]++;
        }

        // 出度为0 入度为N-1
        for (i = 0; i < N; i++) {
                if (ziq[i][0] == 0 && ziq[i][1] == N - 1)
                        return i + 1;
        }
        return -1;
}

int main() { return 0; }
