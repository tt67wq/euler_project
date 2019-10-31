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

void pos_exchange(char *S, int i, int j) {
        char tmp;
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
}

bool is_letter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

char *reverseOnlyLetters(char *S) {
        int i, j, l;

        l = strlen(S);
        j = l - 1;
        i = 0;
        while (i < j) {
                if (is_letter(S[i]) && is_letter(S[j])) {
                        pos_exchange(S, i, j);
                        i++;
                        j--;
                        continue;
                }

                if (is_letter(S[i])) {
                        j--;
                        continue;
                }
                if (is_letter(S[j])) {
                        i++;
                        continue;
                }
                i++;
                j--;
        }
        return S;
}

int main() {
        char s[] = "Test1ng-Leet=code-Q!";
        reverseOnlyLetters(s);
        printf("%s\n", s);
        return 0;
}
