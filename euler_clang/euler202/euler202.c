/*
 * =====================================================================================
 *
 *       Filename:  euler202.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-05-23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int64_t ut;

ut gcd(ut m, ut n) {
        ut r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

void count(ut level, ut row, ut *acc) {
        while (level > 0) {
                if (level % 2) {
                        level -= 3;
                        row += 3;
                } else {
                        ut a = level >> 1;
                        ut b = level + row - a;
                        if (gcd(a, b) == 1) {
                                level -= 3;
                                row += 3;
                                (*acc)++;
                        } else {
                                level -= 3;
                                row += 3;
                        }
                }
        }
}

int main(int argc, const char *argv[]) {

        ut res = 0;
        count(6008819572, 3, &res);
        printf("%llu\n", res);

        return 1;
}
