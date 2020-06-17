/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-17
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define MAX_NUM 2000

static char newArray[MAX_NUM + 1];

int flipgame(int *fronts, int frontsSize, int *backs, int backsSize) {

        memset(newArray, 0, sizeof(char) * (MAX_NUM + 1));

        // if fronts[i] == backs[i], skip it
        for (int i = 0; i < frontsSize; i++) {
                if (fronts[i] == backs[i]) {
                        newArray[fronts[i]] = 1;
                }
        }

        int min = INT_MAX;
        for (int i = 0; i < frontsSize; i++) {
                if (newArray[fronts[i]] == 0) {
                        min = fronts[i] < min ? fronts[i] : min;
                }
                if (newArray[backs[i]] == 0) {
                        min = backs[i] < min ? backs[i] : min;
                }
        }
        if (min == INT_MAX) {
                return 0;
        }
        return min;
}

int main() {
        int fronts[] = {1, 2, 4, 4, 7};
        int backs[] = {1, 3, 4, 1, 2};
        int ans = flipgame(fronts, 5, backs, 5);
        printf("%d\n", ans);
        return 0;
}