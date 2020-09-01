/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

char *toHex(int num) {
        char table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        char *ans = (char *)calloc(9, sizeof(char));

        int idx = 7, cnt = 8;

        do {
                int lowbit4 = num & 0xf;
                ans[idx--] = table[lowbit4];
                num >>= 4;
                cnt -= 1;
        } while (num != 0 && cnt > 0);
        return ans + idx + 1;
}

int main() { return 0; }