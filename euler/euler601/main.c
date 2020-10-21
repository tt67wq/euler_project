/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-10-20
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

typedef unsigned long long ull;

ull gcd(ull m, ull n) {
        ull r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

ull lcm(ull m, ull n) { return m * (n / gcd(m, n)); }

// int streak(int n) {
//         int x = 0;

//         while (0 == ((n + x) % (x + 1))) {
//                 x++;
//         }
//         return x;
// }

int P(int s, ull N) {
        int ans = 0;
        ull m1 = 1;
        for (int i = 2; i <= s; i++) {
                m1 = lcm(m1, i);
        }
        ull m2 = lcm(m1, s + 1);

        ans = (int)((N - 2) / m1 - (N - 2) / m2);

        return ans;
}

int main() {
        int ans = 0;
        for (int i = 1; i <= 31; i++) {
                int _ans = P(i, (ull)pow(4, i));
                printf("P(%d, 4^%d) = %d\n", i, i, _ans);
                ans += _ans;
        }
        printf("%d\n", ans);
        return 0;
}