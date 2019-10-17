/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int trapRainWater(int **heightMap, int heightMapSize, int heightMapColSize) {
        int i, j, h, tmp;
        int res = 0;
        int **rains;

        rains = (int **)calloc(heightMapSize, sizeof(int *));
        for (i = 0; i < heightMapSize; i++) {
                rains[i] = (int *)calloc(heightMapColSize, sizeof(int));
        }

        for (i = 1; i < heightMapSize - 1; i++) {
                for (j = 1; j < heightMapColSize - 1; j++) {
                        h = heightMap[i][j];
                        if (h <= heightMap[i - 1][j] &&
                            h <= heightMap[i + 1][j] &&
                            h <= heightMap[i][j - 1] &&
                            h <= heightMap[i][j + 1]) {
                                res += 1;
                                rains[i][j] += 1;
                        } else {
                        }
                }
        }
}

int main() {
        int i, j;
        int **rains;
        rains = (int **)calloc(3, sizeof(int *));

        for (i = 0; i < 3; i++) {
                rains[i] = (int *)calloc(4, sizeof(int));
                /* for (j = 0; j < 4; j++) { */
                /*         printf("%d\t", rains[i][j]); */
                /* } */
                /* printf("\n"); */
        }

        for (i = 0; i < 3; i++) {

                for (j = 0; j < 4; j++) {
                        printf("%d\t", rains[i][j]);
                }
                printf("\n");
        }

        return 0;
}
