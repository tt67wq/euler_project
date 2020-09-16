/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-09-15
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

#define CN2(n) ((n) * ((n) + 1) / 2)
// 3 -> 1    1
// 4 -> 3    3
// 5 -> 6    6
// 6 -> 12   10 + 1*2

void H(int n, long *count) {
        int s = 1;
        while (n > 0) {
                *count += s * (long)CN2(n);
                s++;
                n -= 3;
        }
}

// void countHexagon(int n, long *count) {
//         for (int i = 0; i < n / 3 + 1; i++) {
//                 long x = n - 3 * i + 1;
//                 *count += (i * x * (x + 1) * (x + 2) / 6);
//         }
// }

int main() {
        long count = 0, total = 0;

        for (int i = 3; i <= 12345; i++) {
                H(i, &count);
                total += count;
        }
        printf("%ld\n", count);
        return 0;
}