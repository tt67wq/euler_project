/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

/* https://leetcode-cn.com/problems/integer-replacement/ */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int ui;

ui min(ui a, ui b) { return a > b ? b : a; }

ui integerReplacement(ui n) {
        ui s = 0;
        while (n != 1) {
                if (n % 2 == 0) {
                        n >>= 1;
                        s++;
                } else {
                        s++;
                        s += min(integerReplacement(n - 1),
                                 integerReplacement(n + 1));
                        break;
                }
        }
        return s;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", integerReplacement(n));
        }
        return 0;
}
