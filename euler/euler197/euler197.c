/*
 * =====================================================================================
 *
 *       Filename:  euler197.c
 *
 *    Description:  欧拉计划197题
 *
 *        Version:  1.0
 *        Created:  2019-04-29
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

typedef kvec_t(double) array;

#define K 30.403243784
#define P 1.0e-9

double f(double x) { return pow(2, K - x * x) * P; }

void fill_u(int n, int index, array *u) {
        if (index == n)
                return;
        double prev = kv_A(*u, kv_size(*u) - 1);
        kv_push(double, *u, f(prev));
        fill_u(n, index + 1, u);
}

int main(int argc, const char *argv[]) {
        array u;
        kv_init(u);
        kv_push(double, u, -1);

        fill_u(1000, 0, &u);

        for (int i = 0; i < kv_size(u); i++) {
                /* printf("%.9f\n", kv_A(u, i)); */
                if (i) {
                        double tmp = kv_A(u, i) + kv_A(u, i - 1);
                        printf("un + un-1 = %.12f, sqrt = %.12f\n", tmp, tmp * tmp);
                }
        }
        return 0;
}
