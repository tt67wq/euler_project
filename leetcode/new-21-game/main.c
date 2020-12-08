/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-12-04
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

double new21Game(int N, int K, int W) {
        if (N < K) {
                return 0.0;
        }
        if (K == 0) {
                return 1.0;
        }

        if (K + W - 1 <= N) {
                return 1.0;
        }

        double dp[K + W];

        for (int i = K; i <= N; i++) {
                dp[i] = 1.0;
        }
        for (int i = N + 1; i <= K + W - 1; i++) {
                dp[i] = 0;
        }

        int j = K - 1;
        double windowSum = 0;
        for (int i = 1; i <= W; i++) {
                windowSum += dp[j + i];
        }
        dp[j] = windowSum / W;
        j--;

        while (j >= 0) {
                windowSum = windowSum + dp[j + 1] - dp[j + W + 1];
                dp[j] = windowSum / W;
                j--;
        }

        return dp[0];
}

int main() {
        double res = new21Game(168, 127, 73);
        printf("%.5f\n", res);
        return 0;
}