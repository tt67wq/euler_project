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

char nextGreatestLetter(char *letters, int lettersSize, char target) {
        int i;
        for (i = 0; i < lettersSize; i++) {
                if (letters[i] > target) {
                        return letters[i];
                }
        }
        return letters[0];
}
int main() { return 0; }
