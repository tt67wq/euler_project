/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-26
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

#define DEBUG
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int dp(int *piles, int i, int j, int pilesSize, int **cache) {
        if (i > j) {
                return 0;
        }
        if (cache[i][j] != 0) {
                return cache[i][j];
        }
        int res;
        if ((j + i + pilesSize) % 2) {
                // first player
                res = MAX(piles[i] + dp(piles, i + 1, j, pilesSize, cache),
                          piles[j] + dp(piles, i, j - 1, pilesSize, cache));
        } else {
                res = MAX(-piles[i] + dp(piles, i + 1, j, pilesSize, cache),
                          -piles[j] + dp(piles, i, j - 1, pilesSize, cache));
        }
        cache[i][j] = res;
        return res;
}

bool stoneGame(int *piles, int pilesSize) {
        int **cache = (int **)malloc(sizeof(int *) * pilesSize);
        for (int i = 0; i < pilesSize; i++) {
                cache[i] = (int *)calloc(sizeof(int), pilesSize);
        }
        bool ans = dp(piles, 0, pilesSize - 1, pilesSize, cache) > 0;
        for (int i = 0; i < pilesSize; i++) {
                free(cache[i]);
        }
        free(cache);
        return ans;
}

int main() {
        int piles[] = {5, 17, 19, 1, 15, 19, 11, 9, 6, 5, 11, 7, 12, 12, 2, 14, 3, 6, 18, 3};
        bool res = stoneGame(piles, 20);
        printf("%d\n", res);
        return 0;
}