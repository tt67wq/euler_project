/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-29
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool judgeSquareSum(int c) {
        int a = 0;
        int b = (int)ceil(sqrt(c));

        while (a <= b) {
                long _c = (long)a * a + (long)b * b;
                if (_c == c) {
                        return true;
                } else if (_c < c) {
                        a++;
                } else {
                        b--;
                }
        }
        return false;
}

int main() {
        int c = judgeSquareSum(2147482647);
        printf("%d\n", c);
        return 0;
}