/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-09
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

#define VALID_PALINDOME(s) (valid((s)))

bool valid(char *s) {
        int i, j;

        i = 0;
        j = strlen(s) - 1;

        while (i + 1 <= j) {
                if (s[i] == s[j]) {
                        i++;
                        j--;
                        continue;
                }
                break;
        }
        return i + 1 > j;
}

bool _checkPalindromeFormation(char *a, char *b, int size) {
        int i = 0, j = size - 1;
        while (a[i] == b[j] && i < j) {
                ++i;
                --j;
        }
        if (i >= j) {
                return true;
        }
        // i < j && a[i] != b[j]
        char tmp[j - i + 2];
        tmp[j - i + 1] = '\0';
        strncpy(tmp, a + i, j - i + 1);
        if (VALID_PALINDOME(tmp)) {
                return true;
        }
        strncpy(tmp, b + i, j - i + 1);
        if (VALID_PALINDOME(tmp)) {
                return true;
        }
        return false;
}

bool checkPalindromeFormation(char *a, char *b) {
        if (VALID_PALINDOME(a) || VALID_PALINDOME(b)) {
                return true;
        }
        int size = strlen(a);
        return _checkPalindromeFormation(a, b, size) || _checkPalindromeFormation(b, a, size);
}

int main() {
        char a[] = "ulacfd";
        char b[] = "jizalu";

        bool res = checkPalindromeFormation(a, b);
        printf("%d\n", res);

        return 0;
}