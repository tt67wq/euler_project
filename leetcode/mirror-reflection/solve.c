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

int common_mul(int a, int b) {
        int s = a;
        while (s % b != 0)
                s += a;
        return s;
}

int mirrorReflection(int p, int q) {
        int cm, t1, t2;
        cm = common_mul(p, q);
        t1 = cm / p;
        t2 = cm / q;

        while (t1 > 1)
                t1 -= 2;

        while (t2 > 1)
                t2 -= 2;

        if (t1 == 0 && t2 == 1)
                return 0;
        if (t1 == 1 && t2 == 1)
                return 1;
        if (t1 == 1 && t2 == 0)
                return 2;
        return -1;
}

int main() { return 0; }
