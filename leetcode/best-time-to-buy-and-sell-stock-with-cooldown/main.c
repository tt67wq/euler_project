/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-14
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define Max(a, b) (a) > (b) ? (a) : (b)

int maxProfit(int *prices, int pricesSize) {
        if (pricesSize == 0) {
                return 0;
        }

        // dp[i][j] -> 第i天处于j状态下的收益 j = [0, 1, 2](空仓，持有，冷却)
        int **dp = (int **)calloc(pricesSize, sizeof(int *));
        for (int i = 0; i < pricesSize; i++) {
                dp[i] = (int *)calloc(3, sizeof(int));
        }

        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[0][2] = 0;

        for (int i = 1; i < pricesSize; i++) {
                dp[i][0] = Max(dp[i - 1][0], dp[i - 1][2]);
                dp[i][1] = Max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
                dp[i][2] = dp[i - 1][1] + prices[i];
        }

        int ans = Max(dp[pricesSize - 1][0], dp[pricesSize - 1][2]);

        for (int i = 0; i < pricesSize; i++) {
                free(dp[i]);
        }
        free(dp);

        return ans;
}

int main() {
        int prices[] = {1, 2, 3, 0, 2};
        printf("%d\n", maxProfit(prices, 5));
        return 0;
}
