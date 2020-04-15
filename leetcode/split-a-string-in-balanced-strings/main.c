/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-15
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int balancedStringSplit(char *s) {
        int lc = 0, rc = 0, ans = 0;
        while (*s != '\0') {
                if (*s == 'L') {
                        lc++;
                } else {
                        rc++;
                }
                if (lc == rc) {
                        ans++;
                }
                s++;
        }
        return ans;
}

int main() {
        printf("%d\n", balancedStringSplit("RLRRLLRLRL"));
        printf("%d\n", balancedStringSplit("RLLLLRRRLR"));

        return 0;
}
