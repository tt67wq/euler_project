/*
 * =====================================================================================
 *
 *       Filename:  euler67.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-03-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MAXN 500

int main() {
        FILE *in = fopen("p067_triangle.txt", "r");
        int tri[MAXN][MAXN];
        int N;
        int i, j, m;

        assert(in);

        fscanf(in, "%d", &N);
        for (i = 0; i < N; i++) {
                for (j = 0; j <= i; j++) {
                        fscanf(in, "%d", &tri[i][j]);

                        if (i == 0)
                                continue;

                        if (j == 0)
                                tri[i][j] += tri[i - 1][j];
                        else if (j == i)
                                tri[i][j] += tri[i - 1][j - 1];
                        else
                                tri[i][j] += MAX(tri[i - 1][j], tri[i - 1][j - 1]);
                }
        }

        m = 0;
        for (j = 0; j < N; j++)
                m = MAX(m, tri[N - 1][j]);
        printf("%d\n", m);

        return 0;
}
