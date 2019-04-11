/*
 * =====================================================================================
 *
 *       Filename:  euler192.c
 *
 *    Description:  欧拉计划192题
 *
 *        Version:  1.0
 *        Created:  2019-04-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef kvec_t(uint64_t) array;

int nearest_sqrt(int n) {
        int i = 1;
        for (; i * i < n; i++)
                ;
        return i - 1;
}

uint64_t gcd(uint64_t m, uint64_t n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

void best_approximations(array *m, array *n, int k) {
        for (int i = 1; i < 200; i++) {

                kv_push(uint64_t, *n, i);

                int m1 = (int)floor(sqrt(k) * i);
                int m2 = (int)ceil(sqrt(k) * i);
                int t = abs(m1 * m1 - i * i * k) > abs(m2 * m2 - i * i * k) ? m2 : m1;
                kv_push(uint64_t, *m, t);
        }
}

int main() {
        array m, n;
        kv_init(m);
        kv_init(n);
        int k = 13;

        best_approximations(&m, &n, k);
        double d = 100.0;
        uint64_t a, b;

        for (int i = 0; i < kv_size(m); i++) {
                uint64_t mi = kv_A(m, i);
                uint64_t ni = kv_A(n, i);
                uint64_t g = gcd(mi, ni);

                double t = fabs((mi * mi) / (double)(ni * ni) - k);
                if (t < d) {
                        a = mi / g;
                        b = ni / g;
                        d = t;
                }

                printf("%d ==> %llu/%llu, nearest => %llu/%llu\n", i + 1, mi / g, ni / g, a, b);
        }
        return 0;
}
