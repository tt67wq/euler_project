/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-27
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

bool canPermutePalindrome(char *s) {
        int vis[255] = {0};
        int l = strlen(s);
        for (int i = 0; i < l; i++) {
                vis[s[i] - '\0'] += 1;
                vis[s[i] - '\0'] %= 2;
        }
        int c = 0;
        for (int i = 0; i < 255; i++) {
                c += vis[i];
        }

        return c == 1 || c == 0;
}

int main() {
        printf("%d\n", 's' - '\0');
        return 0;
}
