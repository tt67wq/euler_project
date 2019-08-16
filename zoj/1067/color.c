/*
 * =====================================================================================
 *
 *       Filename:  color.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-16
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

typedef struct _rgb {
        int r;
        int g;
        int b;
} rgb;

rgb colors[16];

double distance(int r, int g, int b, int i) { return sqrt((r - colors[i].r) * (r - colors[i].r) + (g - colors[i].g) * (g - colors[i].g) + (b - colors[i].b) * (b - colors[i].b)); }

int solve(int r, int g, int b) {
        int i, k;
        double d, md = 100000;
        for (i = 0; i < 16; i++) {
                d = distance(r, g, b, i);
                if (d == 0.0) {
                        k = i;
                        break;
                }

                if (d < md) {
                        md = d;
                        k = i;
                }
        }
        return k;
}

int main() {
        int i;
        rgb tmp;
        int r, g, b, k;
        for (i = 0; i < 16; i++) {
                scanf("%d %d %d", &tmp.r, &tmp.g, &tmp.b);
                colors[i] = tmp;
        }
        while (1) {
                scanf("%d %d %d", &r, &g, &b);
                if (r == -1 && g == -1 && b == -1)
                        break;
                k = solve(r, g, b);
                printf("(%d,%d,%d) maps to (%d,%d,%d)\n", r, g, b, colors[k].r, colors[k].g, colors[k].b);
        }
        return 0;
}
