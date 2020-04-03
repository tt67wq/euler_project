/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-03
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int consecutiveNumbersSum(int N) {
        N *= 2;
        int ans = 0;
        for (int i = sqrt(N); i >= 1; --i)
                if (N % i == 0 && (i + N / i) & 1)
                        ++ans;
        return ans;
}
int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                printf("%d\n", consecutiveNumbersSum(n));
        }

        return 0;
}
