/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-11
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

int findLUSlength(char *a, char *b) {
        if (strcmp(a, b) == 0)
                return -1;
        int alen = strlen(a), blen = strlen(b);
        return alen > blen ? alen : blen;
}

int main() { return 0; }