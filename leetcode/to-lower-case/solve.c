/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-05
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

char *toLowerCase(char *str) {
        int i, l;
        l = strlen(str);
        for (i = 0; i < l; i++) {
                if (str[i] >= 'A' && str[i] <= 'Z')
                        str[i] = str[i] - 'A' + 'a';
        }

        return str;
}

int main() { return 0; }
