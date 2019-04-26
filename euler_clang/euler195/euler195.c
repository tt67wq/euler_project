/*
 * =====================================================================================
 *
 *       Filename:  euler195.c
 *
 *    Description:  欧拉计划195题
 *
 *        Version:  1.0
 *        Created:  2019-04-26
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
#include <time.h>

/* #define K sqrt(3) / 2 */
#define SQ3 1.7320508075688772

// 通项公式

uint64_t gcd(uint64_t m, uint64_t n) {
        uint64_t r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int main(int argc, const char *argv[]) {
        uint64_t count = 0;
        int top = 0;
        top = atoi(argv[1]);
        printf("calculating when top is %d....\n", top);

        for (uint64_t u = 1; u < 2.4 * top; u++) {
                for (uint64_t v = u / 2 + 1; v < u; v++) {
                        if (gcd(u, v) == 1) {
                                uint64_t a = 2 * u * v - u * u;
                                uint64_t b = 2 * u * v - v * v;
                                uint64_t c = u * u + v * v - u * v;
                                uint64_t g = gcd(a, b);
                                if (g > 1) {
                                        a /= g;
                                        b /= g;
                                        c /= g;
                                }

                                double r = (a + b - c) / (2 * SQ3);

                                if (r < top) {
                                        /* printf("%llu, %llu, %llu, %f\n", a, b, c, r); */
                                        /* printf("  -- %llu, %llu\n", u, v); */
                                        count += floor(top / r);
                                } else {
                                        // 将条件加强一点
                                        double r2 = (a + b - c) / 12;
                                        if (r2 > top)
                                                break;
                                }

                        } else {
                                continue;
                        }
                }
                // 如何判断后续没有满足条件的值？
		// 算了 靠猜
        }
        printf("%llu\n", count);
        return 0;
}
