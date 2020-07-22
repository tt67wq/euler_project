/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-07-22
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

#define DEBUG

char *lastSubstring(char *s) {
        int len = strlen(s);
        int ans = 0;

        for (int i = 1; i < len; i++) {
                if (s[i] <= s[i - 1]) {
                        continue;
                }
                if (strcmp(&s[i], &s[ans]) > 0) {
                        ans = i;
                }
        }
        return &s[ans];
}

int main() {
        printf("%s\n", lastSubstring("leetcode"));
        return 0;
}