/*
 * =====================================================================================
 *
 *       Filename:  euler177.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-25
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
#define PI (atan(1) * 4)

double sn[181];
double cs[181];

void init() {
        int x;
        for (x = 0; x <= 180; x++) {
                sn[x] = sin(x * PI / 180);
                cs[x] = cos(x * PI / 180);
        }
}

unsigned int hash(int a, int b, int c, int d) { return (a << 24) | (b << 16) | (c << 8) | d; }

int main(void) {
        int a, b, c, d, e, f, g, h;
        double x, y, z, df;
        unsigned int hc;
        int count = 0;
        init();
        for (a = 1; a <= 45; a++)
                for (b = a; b <= 180 - a * 3; b++)
                        for (c = a; c <= 180 - 2 * a - b; c++)
                                for (d = a; d <= 180 - a - b - c; d++) {
                                        e = 180 - (b + c + d);
                                        h = 180 - (a + b + c);
                                        x = sn[c + d] / sn[e];
                                        y = sn[c] / sn[h];
                                        z = sqrt(x * x + y * y - 2 * x * y * cs[a]);
                                        df = acos((x * x + z * z - y * y) / (2 * x * z)) * 180 / PI;
                                        f = (int)(df + 0.5);
                                        if (fabs(df - f) > 1e-9)
                                                continue;
                                        if (f < a)
                                                break;
                                        g = 180 - (a + f + h);
                                        if (g < a)
                                                break;
                                        hc = hash(a, b, c, d);
                                        if (hc > hash(c, d, e, f))
                                                continue;
                                        if (hc > hash(e, f, g, h))
                                                continue;
                                        if (hc > hash(g, h, a, b))
                                                continue;
                                        if (hc > hash(b, a, h, g))
                                                continue;
                                        if (hc > hash(d, c, b, a))
                                                continue;
                                        if (hc > hash(f, e, d, c))
                                                continue;
                                        if (hc > hash(h, g, f, e))
                                                continue;
                                        count++;
                                }
        printf("Answer: %d\n", count);
        return 0;
}
