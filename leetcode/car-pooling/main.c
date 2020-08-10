/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-10
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

bool carPooling(int **trips, int tripsSize, int *tripsColSize, int capacity) {
        int *vis = (int *)calloc(1001, sizeof(int));

        for (int i = 0; i < tripsSize; i++) {
                for (int j = trips[i][1]; j < trips[i][2]; j++) {
                        vis[j] += trips[i][0];
                }
        }

        int maxNum = INT32_MIN;
        for (int i = 0; i < 1001; i++) {
                maxNum = maxNum > vis[i] ? maxNum : vis[i];
        }
        printf("%d\n", maxNum);
        free(vis);
        if (capacity >= maxNum) {
                return true;
        }
        return false;
}

int main() {
        // [[2,1,5],[3,5,7]]
        int trip0[] = {2, 1, 5};
        int trip1[] = {3, 5, 7};
        int *trips[] = {trip0, trip1};
        bool res = carPooling(trips, 2, NULL, 3);
        printf("%d\n", res);
        return 0;
}