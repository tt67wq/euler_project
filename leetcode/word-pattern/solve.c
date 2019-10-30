/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-30
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

unsigned int js_hash(char *str, unsigned int len) {
        unsigned int hash = 1315423911;
        unsigned int i = 0;

        for (i = 0; i < len; str++, i++)
                hash ^= ((hash << 5) + (*str) + (hash >> 2));

        return hash;
}

bool wordPattern(char *pattern, char *str) {
        int i, j, c, l1, l2;
        unsigned int h;
        unsigned int tb[26] = {0};
        unsigned int rtb[4096] = {0};
        char buffer[500] = {0};

        l1 = strlen(str);
        l2 = strlen(pattern);
        i = 0;
        j = 0;
        c = 0;
        while (c < l2) {
                if (i > l1)
                        return false;
                if (str[i] == ' ' || i == l1) {
                        h = js_hash(buffer, j);
                        /* printf("hash(%s) = %u\n", buffer, h); */
                        if (tb[pattern[c] - 'a'] == 0)
                                tb[pattern[c] - 'a'] = h;
                        else if (tb[pattern[c] - 'a'] != h)
                                return false;
                        else
                                ;

                        if (rtb[h % 4096] == 0)
                                rtb[h % 4096] = pattern[c] - 'a' + 1;
                        else if (rtb[h % 4096] != (pattern[c] - 'a' + 1))
                                return false;
                        else
                                ;

                        ++c;
                        ++i;
                        j = 0;
                        bzero(buffer, 500 * sizeof(char));
                        continue;
                }
                buffer[j++] = str[i++];
        }
        if (i < l1)
                return false;

        return true;
}

int main() {
        char pattern[] = "ab";
        char str[] = "dog dog";
        printf("%d\n", wordPattern(pattern, str));
        return 0;
}
