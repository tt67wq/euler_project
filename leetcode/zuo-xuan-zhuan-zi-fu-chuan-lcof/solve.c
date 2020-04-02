/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-02
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

char *reverseLeftWords(char *s, int n) {
        int l = strlen(s);
        n = n > l ? n % l : n;
        int size = sizeof(char) * (l + 1);
        char *ans = (char *)malloc(size);

        char *p0 = s;
        char *p1 = ans;
        p0 += n;
        p1 += (l - n);

        strncpy(ans, p0, sizeof(char) * (l - n));
        strncpy(p1, s, sizeof(char) * n);

        ans[l] = '\0';

        return ans;
}

int main() {
        char *a = reverseLeftWords("abcdefg", 2);
        char *b = reverseLeftWords("lrloseumgh", 6);
        printf("%s\n", a);
        printf("%s\n", b);
        free(a);
        free(b);
        return 0;
}
