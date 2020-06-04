/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-03
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

int projectionArea(int **grid, int gridSize, int *gridColSize) {
        int ans = 0;
        // 俯视图
        for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridColSize[i]; j++) {
                        if (grid[i][j] > 0) {
                                ans++;
                        }
                }
        }

        // 左视图
        for (int i = 0; i < gridSize; i++) {
                // get max of grid[i]
                int m = 0;
                for (int j = 0; j < gridColSize[i]; j++) {
                        m = m > grid[i][j] ? m : grid[i][j];
                }
                ans += m;
        }

        // 右视图
        int mSize = 0;
        for (int i = 0; i < gridSize; i++) {
                mSize = mSize > gridColSize[i] ? mSize : gridColSize[i];
        }

        // get max of grid[][i]
        for (int i = 0; i < mSize; i++) {
                int m = 0;
                for (int j = 0; j < gridSize; j++) {
                        if (gridColSize[j] > i) {
                                m = m > grid[j][i] ? m : grid[j][i];
                        } else {
                                // pass
                        }
                }
                ans += m;
        }
        return ans;
}

int main() { return 0; }
