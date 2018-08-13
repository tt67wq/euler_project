/*
 * =====================================================================================
 *
 *       Filename:  miller_rabin.c
 *
 *    Description:  米勒罗宾素数判断方法
 *
 *        Version:  1.0
 *        Created:  2018-08-13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long U8;
typedef int bool;

const bool true = 1;
const bool false = 0;

U8 modMultiply(U8 a, U8 b, U8 m) { return a * b % m; }

U8 modPow(U8 a, U8 b, U8 m) {
        U8 v = 1;
        for (U8 p = a % m; b > 0; b >>= 1, p = modMultiply(p, p, m))
                if (b & 1)
                        v = modMultiply(v, p, m);
        return v;
}

bool witness(U8 a, U8 n) {
        U8 n1 = n - 1, s2 = n1 & -n1, x = modPow(a, n1 / s2, n);
        if (x == 1 || x == n1)
                return false;
        for (; s2 > 1; s2 >>= 1) {
                x = modMultiply(x, x, n);
                if (x == 1)
                        return true;
                if (x == n1)
                        return false;
        }
        return true;
}

U8 random2(U8 high) { return (U8)(high * (rand() / (double)RAND_MAX)); }

bool probablyPrime(U8 n, int k) {
        if (n == 2 || n == 3)
                return 1;
        if (n < 2 || n % 2 == 0)
                return 0;
        while (k-- > 0)
                if (witness(random2(n - 3) + 2, n))
                        return false;
        return true;
}

int main() {
        int t;
        scanf("%d", &t);

        while (t-- > 0) {
                U8 n;
                scanf("%llu", &n);
                printf("prime?: %d\n", probablyPrime(n, 3));
        }
        return 0;
}
