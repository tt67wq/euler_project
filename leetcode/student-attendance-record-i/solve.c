/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-31
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

bool checkRecord(char *s) {
        int i, l, as, ls;
        l = strlen(s);

        as = 0;
        ls = 0;

        for (i = 0; i < l; i++) {
                if (s[i] == 'L') {
                        ls++;
                        if (ls == 3) {
                                return false;
                        }
                } else {
                        ls = 0;
                        if (s[i] == 'A') {
                                as++;
                                if (as == 2) {
                                        return false;
                                }
                        }
                }
        }
	return true;
}

int main() { return 0; }
