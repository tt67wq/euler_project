/*
 * =====================================================================================
 *
 *       Filename:  euler216.c
 *
 *    Description:  欧拉计划216题
 *
 *        Version:  1.0
 *        Created:  2019-07-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 50000000LL

typedef unsigned long long ull;

//////////////////    prime check

// 计算 m^n % k
ull pow_mod(ull m, ull n, ull k) {
        if (n == 1)
                return m % k;
        if (n == 2)
                return (m * m) % k;

        if (m % k == 0)
                return 0;

        ull b = pow_mod(m, 2, k);
        if (n % 2 == 0) {
                return pow_mod(b, n >> 1, k);
        } else {
                return (m * pow_mod(b, (n - 1) >> 1, k)) % k;
        }
}

ull random2(ull high) {
        if (high == 2)
                return 2;
        return rand() % (high - 2) + 2;
}

// 二次探测
int double_check(ull tu, ull n, ull x) {
        /* printf("tu => %d, n => %d, x =>%d\n", tu, n, x); */
        if (tu >= n)
                return x;
        ull y = pow_mod(x, 2, n);

        if (y == 1 && x != 1 && x != n - 1)
                return 0;
        else
                return double_check(tu << 1, n, y);
}

ull get_u(ull u) {
        while (1) {
                if (u % 2 == 1)
                        break;
                u = u >> 1;
        }
        return u;
}

// 费马检测
int fermat_check(ull n, ull u, int s) {
        if (s == 0)
                return 1;
        ull a = random2(n - 1);
        ull x = pow_mod(a, u, n);
        int flag = double_check(u, n, x);

        if (flag > 0) {
                if (flag == 1)
                        return fermat_check(n, u, s - 1);
                else
                        return 0;
        } else
                return 0;
}

int probablyPrime(ull n, int times) {
        if (n == 1)
                return 0;
        if (n == 2)
                return 1;
        if (n % 2 == 0)
                return 0;
        return fermat_check(n, get_u(n - 1), times);
}

ull t(ull n) { return 2 * n * n - 1; }

int main(int argc, const char *argv[]) {
        int total = 0;

        for (ull i = 2; i <= MAX; i++) {
                if (probablyPrime(t(i), 3)) {
                        printf("t(%llu) = %llu\n", i, t(i));
                        total++;
                }
        }

        printf("total = %d\n", total);
        return 0;
}
