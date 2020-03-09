/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-03-09
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int reverseBits(int num) {
        if (num == 0x7fffffff) {
                return 32;
        }
        int n, change, notChange, res;
        n = 1;
        change = 0;
        notChange = 0;
        res = 0;

        while (n > 0) {
                if ((n & num) > 0) {
                        // bit  n == 1
                        change += 1;
                        notChange += 1;
                } else { // bit  n == 0
                        change = notChange + 1;
                        notChange = 0;
                }
                res = res > change ? res : change;
                if ((long)n * 2 > 0x7fffffff) {
                        break;
                }
                n <<= 1;
        }
        return res;
}

int main() {
        printf("%d\n", reverseBits(7));
        printf("%d\n", reverseBits(1775));
        printf("%d\n", reverseBits(0x7fffffff));
        return 0;
}
