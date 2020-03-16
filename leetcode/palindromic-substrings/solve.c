/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-16
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstrings(char *s) {
        int len = strlen(s);
        int *dp = (int *)calloc(len, sizeof(int));
        int cnt = 0;

        for (int i = 0; i < len; i++) {
                dp[i] = 1;
                cnt++;
                for (int j = 0; j < i; j++) {
                        if (s[j] == s[i] && dp[j + 1] == 1) {
                                dp[j] = 1;
                                cnt++;
                        } else {
                                dp[j] = 0;
                        }
                }
        }
	free(dp);
        return cnt;
}

int main() {
        printf("%d\n", countSubstrings("abc"));
        return 0;
}
