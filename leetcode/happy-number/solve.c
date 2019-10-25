/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-25
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

#define MAX 1000

char cache[MAX / 8 + 1];

bool isHappy(int n) {
        int t, s = 0;

        bzero(cache, (MAX / 8 + 1) * sizeof(char));

        while (n > 1) {
                /* printf("%d\n", n); */
                while (n > 0) {
                        t = n % 10;
                        s += t * t;
                        n /= 10;
                }

                if (cache[s / 8] & (1 << (s % 8 / 2))) {
                        break;
                }
                n = s;
                s = 0;
                cache[n / 8] |= (1 << (n % 8 / 2));
        }
        return n == 1;
}

int main() {
        printf("%d\n", isHappy(19));
        return 0;
}
