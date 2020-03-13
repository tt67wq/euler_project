/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/* 0 1 2 */
/* 3 4 5 */
/* 6 7 8 */
int win(int *vis) {
        // 行
        for (int i = 0; i < 3; i++) {
                if (vis[i * 3] == 1 && vis[i * 3 + 1] == 1 && vis[i * 3 + 2] == 1) {
                        return TRUE;
                }
        }
        // 列
        for (int i = 0; i < 3; i++) {
                if (vis[i] == 1 && vis[3 + i] == 1 && vis[6 + i] == 1) {
                        return TRUE;
                }
        }
        // 对角
        if ((vis[0] == 1 && vis[4] == 1 && vis[8] == 1) ||
            (vis[2] == 1 && vis[4] == 1 && vis[6] == 1)) {
                return TRUE;
        }

        return FALSE;
}

char *tictactoe(int **moves, int movesSize, int *movesColSize) {
        int as[9] = {0};
        int bs[9] = {0};

        for (int i = 0; i < movesSize; i++) {
                int p = moves[i][0] * 3 + moves[i][1];
                if (i % 2 == 0) {
                        as[p] = 1;
                } else {
                        bs[p] = 1;
                }
                // check
                if (i >= 4) {
                        if (i % 2 == 0 && win(as) == TRUE) {
                                return "A";
                        }
                        if (i % 2 == 1 && win(bs) == TRUE) {
                                return "B";
                        }
                }
        }
        if (movesSize == 9) {
                return "Draw";
        }
        return "Pending";
}

int main() { return 0; }
