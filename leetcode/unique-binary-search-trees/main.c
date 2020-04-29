/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-29
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

int numTrees(int n) {
        // dp[i] -> numTrees(i)
        if (n < 3) {
                return n;
        }
        int *dp = (int *)calloc(n + 1, sizeof(int));
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; i++) {
                // j -> left nums
                if (i & 1) {
                        for (int j = 0; 2 * j < i - 1; j++) {
                                dp[i] += 2 * (dp[j] * dp[i - 1 - j]);
                        }
                        dp[i] += dp[(i - 1) / 2] * dp[(i - 1) / 2];
                } else {
                        for (int j = 0; 2 * j < i; j++) {
                                dp[i] += 2 * (dp[j] * dp[i - 1 - j]);
                        }
                }
        }

#ifdef DEBUG
        for (int i = 0; i < n + 1; i++) {
                printf("dp[%d] = %d\n", i, dp[i]);
        }
#endif

        int ans = dp[n];
        free(dp);
        return ans;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", numTrees(n));
        }
        return 0;
}
