/*
 * =====================================================================================
 *
 *       Filename:  euler_problem27.c
 *
 *    Description:  欧拉计划27题
 *
 *        version:  1.0
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

int abs(int n) { return n > 0 ? n : -n; }

int prime_chain_length(int a, int b) {
        int n = 0;
        int l = 0;
        while (1) {
                if (probablyPrime((U8)abs(n * n + a * n + b), 3)) {
                        n++;
                        l++;
                } else {
                        break;
                }
        }
        return l;
}

int main() {
        clock_t begin = clock();

        int b[168] = {0};
        int j = 0;
        int max_chain_len = 0;
        int max_chain_a;
        int max_chain_b;
        for (U8 i = 2; i <= 1000; i++)
                if (probablyPrime(i, 3))
                        b[j++] = i;

        for (int i = -1000; i <= 1000; i++) {
                for (int j = 0; j < 167; j++) {
                        int t = prime_chain_length(i, b[j]);
                        if (t > max_chain_len) {
                                max_chain_len = t;
                                max_chain_a = i;
                                max_chain_b = b[j];
                        }
                }
        }
        clock_t end = clock();
        double timespent = end - begin;

        printf("max_chain_len => %d, a => %d, b => %d\n", max_chain_len, max_chain_a, max_chain_b);
        printf("result => %d time use => %lfs\n", max_chain_a * max_chain_b,
               (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
