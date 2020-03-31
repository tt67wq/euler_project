/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-31
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int M;
int N;

int dfs(int x, int y, int *cache) {
        if (x == M && y == N) {
                return 1;
        }
        int f = x * (N + 1) + y;
        /* printf("x: %d, y: %d, f: %d\n", x, y, f); */
        if (cache[f] != 0) {
                return cache[f];
        }

        // down
        int ans = 0;
        if (y < N) {
                ans += dfs(x, y + 1, cache);
        }

        // right
        if (x < M) {
                ans += dfs(x + 1, y, cache);
        }
        cache[f] = ans;
        return ans;
}

int uniquePaths(int m, int n) {
        M = m - 1;
        N = n - 1;
        int *cache = (int *)calloc(m * n, sizeof(int));
        int ans = dfs(0, 0, cache);
        free(cache);
        return ans;
}

int main() {
        printf("%d\n", uniquePaths(3, 2));
        printf("%d\n", uniquePaths(7, 3));
        return 0;
}
