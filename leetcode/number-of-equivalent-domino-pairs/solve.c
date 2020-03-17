/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-17
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int numEquivDominoPairs(int **dominoes, int dominoesSize, int *dominoesColSize) {
        int vis[10][10] = {0};

        {
                int a, b;
                for (int i = 0; i < dominoesSize; i++) {
                        a = dominoes[i][0];
                        b = dominoes[i][1];
                        if (a > b) {
                                int tmp = a;
                                a = b;
                                b = tmp;
                        }
                        vis[a][b]++;
                }
        }
        int c = 0;
        for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                        if (vis[i][j] > 1) {
                                c += vis[i][j] * (vis[i][j] - 1) / 2;
                        }
                }
        }
        return c;
}

int main() {
        int domines[][2] = {{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}};
        printf("%d\n", numEquivDominoPairs(domines, 5, 2));
        return 0;
}
