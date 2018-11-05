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

int modMultiply(int a, int b, int m) { return a * b % m; }

int modPow(int a, int b, int m) {
        int v = 1;
        for (int p = a % m; b > 0; b >>= 1, p = modMultiply(p, p, m))
                if (b & 1)
                        v = modMultiply(v, p, m);
        return v;
}

int witness(int a, int n) {
        int n1 = n - 1, s2 = n1 & -n1, x = modPow(a, n1 / s2, n);
        if (x == 1 || x == n1)
                return 0;
        for (; s2 > 1; s2 >>= 1) {
                x = modMultiply(x, x, n);
                if (x == 1)
                        return 1;
                if (x == n1)
                        return 0;
        }
        return 1;
}

int random2(int high) { return (int)(high * (rand() / (double)RAND_MAX)); }

int probablyPrime(int n, int k) {
        if (n == 1)
                return 0;
        if (n == 2 || n == 3)
                return 1;
        if (n < 2 || n % 2 == 0)
                return 0;
        while (k-- > 0)
                if (witness(random2(n - 3) + 2, n))
                        return 0;
        return 1;
}
