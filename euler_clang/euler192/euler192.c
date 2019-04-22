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

#define TOP 1000

/* 57060635927998344 */

typedef kvec_t(int64_t) array;

int nearest_sqrt(int n) {
        int i = 1;
        for (; i * i < n; i++)
                ;
        return abs((i - 1) * (i - 1) - n) > abs(i * i - n) ? i : i - 1;
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

                kv_push(int64_t, *n, i);

                int m1 = (int)floor(sqrt(k) * i);
                int m2 = (int)ceil(sqrt(k) * i);
                int t = llabs(m1 * m1 - i * i * k) > llabs(m2 * m2 - i * i * k) ? m2 : m1;
                kv_push(int64_t, *m, t);
        }
}

int64_t extend_gcd(int64_t a, int64_t b) {
        int64_t a1 = 0;
        int64_t a2 = 1;

        int64_t b1 = 1;
        int64_t b2 = 0;

        while (b) {
                int64_t c = a / b;
                int64_t tmp = a;
                a = b;
                b = tmp % b;

                tmp = a1;
                a1 = a2 - c * a1;
                a2 = tmp;

                tmp = b1;
                b1 = b2 - c * b1;
                b2 = tmp;
        }
        return a2;
}

int64_t niyuan(int64_t a, int64_t b) {
        int64_t g = extend_gcd(a, b);
        return g > 0 ? g : b + g;
}

void approximations(int k, array *ms, array *ns) {
        int64_t m = kv_A(*ms, kv_size(*ms) - 1);
        int64_t n = kv_A(*ns, kv_size(*ns) - 1);

        if (n > TOP) {
                kv_pop(*ms);
                kv_pop(*ns);
                return;
        }

        double d1 = (double)m / n;
        printf("%llu/%llu", m, n);
        if (d1 * d1 > k) {
                printf(" bigger\n");
                // bigger
                int64_t y0 = niyuan(m, n);
                int64_t x0 = (m * y0 - 1) / n;
                printf("x0 -> %llu, y0 -> %llu\n", x0, y0);
                for (int64_t i = y0 + n, j = x0 + m;; i += n, j += m) {
                        double d2 = (double)j / i;
                        printf(" -- %llu/%llu\n", j, i);
                        if (d2 * d2 > k) {
                                if (d1 > d2) {
                                        kv_push(int64_t, *ms, j);
                                        kv_push(int64_t, *ns, i);
                                        break;
                                }
                        } else {
                                double mid = (d1 + d2) / 2;
                                if (mid * mid > k) {
                                        kv_push(int64_t, *ms, j);
                                        kv_push(int64_t, *ns, i);
                                        break;
                                }
                        }
                        if (i > TOP)
                                return;
                }
        } else {
                printf(" smaller\n");
                // smaller
                int64_t x0 = niyuan(n, m);
                int64_t y0 = (n * x0 - 1) / m;
                printf("x0 -> %llu, y0 -> %llu\n", x0, y0);
                for (int64_t i = x0 + m, j = y0 + n;; i += m, j += n) {
                        double d2 = (double)i / j;
                        printf(" ++ %llu/%llu\n", i, j);
                        if (d2 * d2 < k) {
                                if (d2 >= d1) {
                                        kv_push(int64_t, *ms, i);
                                        kv_push(int64_t, *ns, j);
                                        break;
                                }
                        } else {
                                double mid = (d1 + d2) / 2;
                                if (mid * mid < k) {
                                        kv_push(int64_t, *ms, i);
                                        kv_push(int64_t, *ns, j);
                                        break;
                                }
                        }
                        if (j > TOP)
                                return;
                }
        }
        approximations(k, ms, ns);
}

int main() {
        array ms, ns;
        int j = 1;
        uint64_t s = 0;
        for (int k = 13; k <= 13; k++) {
                while (j * j < k)
                        j++;
                if (j * j == k)
                        continue;

                kv_init(ms);
                kv_init(ns);
                kv_push(int64_t, ns, 1);
                kv_push(int64_t, ms, (int64_t)nearest_sqrt(k));
                approximations(k, &ms, &ns);
                int64_t fm = (uint64_t)kv_pop(ms);
                int64_t fn = (uint64_t)kv_pop(ns);

                printf("%d => %llu/%llu\n", k, fm, fn);
                s += fn;
        }
        printf("%llu\n", s);
        return 0;
}
