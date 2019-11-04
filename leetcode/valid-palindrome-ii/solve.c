/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-04
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

bool valid(char *s, int direction) {
        int i, j;
        bool flag;

        i = 0;
        j = strlen(s) - 1;
        flag = false;

        while (i + 1 <= j) {
                if (s[i] == s[j]) {
                        i++;
                        j--;
                        continue;
                } else {
                        if (!flag) {
                                flag = true;
                                if (direction == 1)
                                        i++;
                                else
                                        j--;
                        } else {
                                break;
                        }
                }
        }
        return i + 1 > j;
}

bool validPalindrome(char *s) { return valid(s, 1) || valid(s, 0); }

int main() {
        char s[100];
        while (1) {
                scanf("%s", s);
                printf("%d\n", validPalindrome(s));
        }
        return 0;
}
