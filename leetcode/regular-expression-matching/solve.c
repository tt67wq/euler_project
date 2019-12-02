/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-29
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
#include <string.h>

bool isMatch(char *s, char *p) {
        int i, j, ls, lp;

        ls = strlen(s);
        lp = strlen(p);

        bool dp[ls + 1][lp + 1];

        dp[0][0] = true;

        /* dp[i][j]代表前i个s与前j个p是否匹配 */
        for (j = 0; j < lp; j++) {
                if (p[j] != '*') {
                        // a
                        // .
                        for (i = 0; i < ls; i++) {
                                if (s[i] == p[j] || p[j] == '.')
                                        dp[i + 1][j + 1] = dp[i][j];
                        }
                } else {
                        // *
                        if (j < 1)
                                continue;

                        if (dp[0][j - 1])
                                dp[0][j + 1] = true;

                        if (p[j - 1] == '.') {
                                // .*
                                i = 0;
                                while (i < ls && !dp[i + 1][j - 1] && !dp[i + 1][j])
                                        i++;

                                for (; i < ls; i++)
                                        dp[i + 1][j + 1] = true;

                        } else {
                                // a*
                                for (i = 0; i < ls; i++)
                                        if (dp[i + 1][j] || dp[i + 1][j - 1] || (i > 0 && dp[i][j + 1] && s[i] == s[i - 1] && s[i - 1] == p[j - 1]))
                                                dp[i + 1][j + 1] = true;
                        }
                }
        }

        /* for (i = 0; i < ls + 1; i++) { */
        /*         for (j = 0; j < lp + 1; j++) { */
        /*                 printf("dp[%d][%d]=%d ", i, j, dp[i][j]); */
        /*         } */
        /*         printf("\n"); */
        /* } */

        return dp[ls][lp];
}

int main() {
        char s[] = "fa";
        char p[] = "f.*a";

        printf("%d\n", isMatch(s, p));

        return 0;
}
