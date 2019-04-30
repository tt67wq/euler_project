/*
 * =====================================================================================
 *
 *       Filename:  euler192_2.c
 *
 *    Description:  欧拉计划192题
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIMIT 1e12

struct Fraction {
        uint64_t n; // 分子
        uint64_t m; // 分母
};

uint64_t gcd(uint64_t m, uint64_t n) {
        uint64_t r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

/* typedef kvec_t(struct Fraction) array; */

void approximations(int target, struct Fraction a, struct Fraction b, struct Fraction *best, int index) {
        struct Fraction c;
        /* printf("a = %llu/%llu, b = %llu/%llu ", a.n, a.m, b.n, b.m); */
        uint64_t g = gcd(a.n + b.n, a.m + b.m);
        c.n = (a.n + b.n) / g;
        c.m = (a.m + b.m) / g;
        /* printf("g = %llu, c = %llu/%llu, index = %d\n", g, c.n, c.m, index); */
        if (c.m > LIMIT || index > 40000) {
                return;
        } else {
                if (fabs(target - pow((double)best->n / best->m, 2)) > fabs(target - pow((double)c.n / c.m, 2))) {
                        *best = c;
                }
        }
        // 判断大小
        if (target > pow((double)c.n / c.m, 2)) {
                // c^2 < target
                approximations(target, c, b, best, ++index);
        } else {
                // c^2 > target
                approximations(target, a, c, best, ++index);
        }
}

int main(int argc, const char *argv[]) {
        int target = 0;
        uint64_t sum = 0;

        for (target = 2; target < 100001; target++) {
                uint64_t sq = (uint64_t)floor(sqrt(target));
                if (sq * sq == target)
                        continue;
                struct Fraction a, b, c;
                a.m = 1;
                b.m = 1;

                a.n = sq;
                b.n = a.n + 1;
                c = a;

                approximations(target, a, b, &c, 0);

                /* printf("target = %d, best = %llu/%llu\n", target, c.n, c.m); */
                sum += c.m;
        }
        printf("%llu\n", sum);

        return 0;
}
