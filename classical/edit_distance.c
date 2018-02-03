/*
 * =====================================================================================
 *
 *       Filename:  edit_distance.c
 *
 *    Description:  字符串距离编辑，动态规划的典型例子
 *
 *        Version:  1.0
 *        Created:  2018-01-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */
/* https://wizardforcel.gitbooks.io/the-art-of-programming-by-july/content/05.02.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))
#define TRUE 1
#define FALSE 0

/* 假如令dp[i][j] 表示源串S[0…i] 和目标串T[0…j] 的最短编辑距离，其边界：dp[0][j]
 * = j，dp[i][0] = i，那么我们可以得出状态转移方程： */
/* dp[i][j] =min{ */
/*     dp[i-1][j] + 1 , S[i]不在T[0…j]中 */
/*     dp[i-1][j-1] + 1/0 , S[i]在T[j] */
/*     dp[i][j-1] + 1 , S[i]在T[0…j-1]中 */
/* } */

int min(int a, int b);
int EditDistance(char *ps, char *pt);

int main() {
        char *ps, *pt;
        int distance;

        ps = "ALGORITHM";
        pt = "ALTRUISTIC";

        printf("ps: %s, pt: %s\n", ps, pt);
        distance = EditDistance(ps, pt);
        printf("min distance is %d\n", distance);
        return 1;
}

int EditDistance(char *ps, char *pt) {
        int srcLength = strlen(ps);
        int targetLength = strlen(pt);
        int i, j;
        printf("src length: %d, target length: %d\n", srcLength, targetLength);
        int dp[srcLength + 1][targetLength + 1];

        memset(dp, 0, sizeof(dp));

        for (i = 0; i <= srcLength; ++i) {
                dp[i][0] = i;
        }

        for (j = 0; j <= targetLength; ++j) {
                dp[0][j] = j;
        }

        for (i = 1; i <= srcLength; ++i) {
                for (j = 1; j <= targetLength; ++j) {
                        if (ps[i - 1] == pt[j - 1]) {
                                dp[i][j] = dp[i - 1][j - 1];
                        } else {
                                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
                        }
                }
        }

        /* for (i = 0; i <= srcLength; ++i) { */
        /* 	for (j = 0; j <= targetLength; ++j) { */
        /* 		printf("dp[%d][%d] = %d\n", i, j, dp[i][j]); */
        /*         } */
        /* } */

        return dp[srcLength][targetLength];
}

int min(int a, int b) {
        if (a > b)
                return b;
        else
                return a;
}
