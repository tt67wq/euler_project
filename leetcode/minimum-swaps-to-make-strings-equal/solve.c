/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-22
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

int minimumSwap(char *s1, char *s2) {
        int xy, yx, l, i;

        xy = 0;
        yx = 0;
        l = strlen(s1);

        for (i = 0; i < l; i++) {
                if (s1[i] != s2[i]) {
                        if (s1[i] == 'x')
                                xy++;
                        else
                                yx++;
                }
        }
        if ((xy + yx) & 1)
                return -1;

        return (xy + 1) / 2 + (yx + 1) / 2;
}

int main() { return 0; }
