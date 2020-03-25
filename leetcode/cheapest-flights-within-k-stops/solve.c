/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-25
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

void dfs(int **mx, int k, int K, int n, int src, int dst, int dis, int *min);

int findCheapestPrice(int n, int **flights, int flightsSize, int *flightsColSize, int src, int dst,
                      int K) {
        int **mx = (int **)calloc(n, sizeof(int *));
        for (int i = 0; i < n; i++) {
                mx[i] = (int *)calloc(n, sizeof(int));
        }

        for (int i = 0; i < flightsSize; i++) {
                int from = flights[i][0];
                int to = flights[i][1];
                int dis = flights[i][2];

                mx[from][to] = dis;
        }
        int ans = INT_MAX;
        dfs(mx, 0, K, n, src, dst, 0, &ans);
        for (int i = 0; i < n; i++) {
                free(mx[i]);
        }
        free(mx);
        if (ans == INT_MAX) {
                ans = -1;
        }
        return ans;
}

void dfs(int **mx, int k, int K, int n, int src, int dst, int dis, int *min) {
        if (k > K + 1) {
                return;
        }
        if (dis > *min) {
                return;
        }

        if (src == dst) {
                // printf("%d\n", dis);
                if (*min > dis) {
                        *min = dis;
                }
                return;
        }

        for (int i = 0; i < n; i++) {
                if (mx[src][i] > 0) {
                        dfs(mx, k + 1, K, n, i, dst, dis + mx[src][i], min);
                }
        }
}

int main() {
        /* [[0,1,100],[1,2,100],[0,2,500]] */
        int f0[] = {0, 1, 100};
        int f1[] = {1, 2, 100};
        int f2[] = {0, 2, 500};

        int *fs[] = {f0, f1, f2};
        printf("%d\n", findCheapestPrice(3, fs, 3, NULL, 0, 2, 1));
        printf("%d\n", findCheapestPrice(3, fs, 3, NULL, 0, 2, 0));
        return 0;
}
