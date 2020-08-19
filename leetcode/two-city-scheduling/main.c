/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-19
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

int cmpfunc(const void *a, const void *b) {
        int da = (*(int **)a)[0] - (*(int **)a)[1];
        int db = (*(int **)b)[0] - (*(int **)b)[1];

        if (da > db) {
                return 1;
        } else if (da < db) {
                return -1;
        } else {
                return 0;
        }
}

int twoCitySchedCost(int **costs, int costsSize, int *costsColSize) {

        // sort by cost[1] - cost[0]
        qsort(costs, costsSize, sizeof(costs[0]), cmpfunc);

        for (int i = 0; i < costsSize; i++) {
                printf("([%d, %d], %d)", costs[i][0], costs[i][1], costs[i][0] - costs[i][1]);
        }
        printf("\n");

        int total = 0;
        int n = costsSize / 2;

        for (int i = 0; i < n; i++) {
                total += (costs[i][0] + costs[i + n][1]);
        }
        return total;
}

int main() {
        int cost0[] = {259, 770};
        int cost1[] = {448, 54};
        int cost2[] = {926, 667};
        int cost3[] = {184, 139};
        int cost4[] = {840, 118};
        int cost5[] = {577, 469};

        int *costs[] = {cost0, cost1, cost2, cost3, cost4, cost5};

        int res = twoCitySchedCost(costs, 6, NULL);
        printf("%d\n", res);
        return 0;
}