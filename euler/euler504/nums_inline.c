/*
 * =====================================================================================
 *
 *       Filename:  nums_inline.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 扩展欧几里得算法
void gcd(int a, int b, int *g, int *x, int *y) {
        if (!b) {
                *g = a;
                *x = 1;
                *y = 0;
        } else {
                gcd(b, a % b, g, y, x);
                *y -= *x * (a / b);
        }
}

int main() {

        int g, x, y;
        int a, b, c;
        int x0, y0;
        int xn, yn;
        int x1, x2, y1, y2;
        int k;
        bool flag_up, flag_down;
        while (1) {
                scanf("%d %d %d", &a, &b, &c);
                scanf("%d %d %d %d", &x1, &x2, &y1, &y2);

                // step1: ax+by=gcd(a,b)的解
                gcd(a, b, &g, &x, &y);
                if (c % g != 0) {
                        printf("no answer\n");
                        continue;
                }

                // step2: ax+by=-c的一个解
                x0 = -x * (c / g);
                y0 = -y * (c / g);

                printf("x0 = %d, y0 = %d\n", x0, y0);
                flag_up = true;
                flag_down = true;

                // step3: 求范围内所有解
                for (k = 1;; k++) {
                        xn = x0 - k * (b / g);
                        yn = y0 + k * (a / g);

                        if (flag_up && (xn >= x1) && (xn <= x2) && (yn >= y1) &&
                            (yn <= y2)) {
                                printf("%d %d\n", xn, yn);
                        } else {
                                flag_up = false;
                        }
                        xn = x0 + k * (b / g);
                        yn = y0 - k * (a / g);
                        if (flag_down && (xn >= x1) && (xn <= x2) &&
                            (yn >= y1) && (yn <= y2)) {
                                printf("%d %d\n", xn, yn);
                        } else {
                                flag_down = false;
                        }

                        if (!flag_up && !flag_down)
                                break;
                }
        }
        return 0;
}
