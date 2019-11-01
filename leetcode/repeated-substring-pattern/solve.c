/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-31
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

bool repeatedSubstringPattern(char *s) {
        int i, j, k, l;
        l = strlen(s);

        for (i = 1; i < l; i++) {
                if (s[i] == s[0]) {
                        j = i;
                        k = 0;
                        while (j < l) {
                                if (s[j] != s[k])
                                        break;
                                j++;
                                k++;
                        }
                        if (j == l)
                                return l % (j - k) == 0;
                }
        }
        return false;
}

int main() {
        char s[] = "abab";
        printf("%d\n", repeatedSubstringPattern(s));
        return 0;
}
