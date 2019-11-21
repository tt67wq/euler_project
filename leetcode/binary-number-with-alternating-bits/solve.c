/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-20
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

bool hasAlternatingBits(int n) {
        int a, b;
        bool ans = true;

        b = n % 2;
        n >>= 1;

        while (n > 0) {
                a = n % 2;
                if (a == b) {
                        ans = false;
                        break;
                }

                n >>= 1;
                b = a;
        }
        return ans;
}

int main() { return 0; }
