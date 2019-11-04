/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-04
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int islandPerimeter(int **grid, int gridSize, int *gridColSize) {
        int i, j, s;
        s = 0;
        for (i = 0; i < gridSize; i++) {
                for (j = 0; j < gridColSize[i]; j++) {
                        if (grid[i][j] == 1) {
                                s += 4;
                                // up
                                if (i > 0 && gridColSize[i - 1] >= gridColSize[i] && grid[i - 1][j] == 1)
                                        s -= 2;

                                // left
                                if (j > 0 && grid[i][j - 1] == 1)
                                        s -= 2;
                        }
                }
        }
        return s;
}

int main() { return 0; }
