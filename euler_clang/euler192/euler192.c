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

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

long long limit = 1000000000000LL;

int a[64];
long long den[64];

int isqrt(int n) {
        int r = (int)floor(sqrt(n));
        while (r * r > n)
                r--;
        while (r * (r + 2) < n)
                r++;
        return r;
}

long long best(int n) {
        int r = isqrt(n);
        if (r * r == n) {
                return 0;
        }
        a[0] = r;
        den[0] = 1;
        int b = r, c = n - b * b;
        a[1] = (b + r) / c;
        den[1] = a[1];
        int i = 1;
        while (den[i] < limit) {
                b = a[i] * c - b;
                c = (n - b * b) / c;
                i++;
                a[i] = (b + r) / c;
                den[i] = a[i] * den[i - 1] + den[i - 2];
        }
        if (den[i] == limit) {
                return limit;
        }
        i--;
        int j = (int)((limit - den[i - 1]) / den[i]);
        long long can = j * den[i] + den[i - 1];
        int a2 = a[i + 1];
        if ((j << 1) > a2) {
                return can;
        }
        if ((j << 1) < a2) {
                return den[i];
        }
        b = a2 * c - b;
        c = (n - b * b) / c;
        a2 = (b + r) / c;
        j = i;
        while (j > 0 && a[j] == a2) {
                j--;
                b = a2 * c - b;
                c = (n - b * b) / c;
                a2 = (b + r) / c;
        }
        if (j == 0) {
                return ((i & 1)) ? can : den[i];
        } else {
                if (((i - j) & 1)) {
                        a2 = a[j] - a2;
                } else {
                        a2 -= a[j];
                }
                return (a2 > 0) ? can : den[i];
        }
}

int main(int argc, const char *argv[]) {
        /* double start, stop; */
        /* long long sum = 0; */
        /* int n; */
        /* start = clock(); */
        /* for (n = 2; n < 100001; n++) { */
        /*         sum += best(n); */
        /* } */
        /* stop = clock(); */
        /* printf("%lld\n", sum); */
        /* printf("%.3lf s\n", (stop - start) / CLOCKS_PER_SEC); */
        /* return 0; */
        int target = 0;
        target = atoi(argv[1]);
        printf("%lld\n", best(target));
        return 0;
}
