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

#include "prime.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ull modMultiply(ull a, ull b, ull m) { return a * b % m; }

ull modPow(ull a, ull b, ull m) {
        ull v = 1;
        for (ull p = a % m; b > 0; b >>= 1, p = modMultiply(p, p, m))
                if (b & 1)
                        v = modMultiply(v, p, m);
        return v;
}

bool witness(ull a, ull n) {
        ull n1 = n - 1, s2 = n1 & -n1, x = modPow(a, n1 / s2, n);
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

ull random2(ull high) { return (ull)(high * (rand() / (double)RAND_MAX)); }

bool probablyPrime(ull n, int k) {
        if (n == 2 || n == 3)
                return 1;
        if (n < 2 || n % 2 == 0)
                return 0;
        while (k-- > 0)
                if (witness(random2(n - 3) + 2, n))
                        return false;
        return true;
}
