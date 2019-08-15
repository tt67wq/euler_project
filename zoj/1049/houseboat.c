/*
 * =====================================================================================
 *
 *       Filename:  houseboat.c
 *
 *    Description:  zoj 1049
 *
 *        Version:  1.0
 *        Created:  2019-08-15
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

#define MAX 100
#define PI 3.141592653589793

double rs[MAX + 1];

void init() {
        int i;
        for (i = 1; i < MAX + 1; i++)
                rs[i] = sqrt((double)(i * 100) / PI);
        rs[0] = 0.0;
}

int bin_search(double d) {
        int h, t, m;
        h = 0;
        t = MAX;
        while (h < t - 1) {
                m = (h + t) >> 1;
                if (d > rs[m]) {
                        h = m;
                } else {
                        t = m;
                }
        }
        return t;
}

int years(double x, double y) { return bin_search(sqrt(x * x + y * y)); }

int main() {
        init();
        int n, i = 1;
        double x, y;
        scanf("%d", &n);
        while (n > 0) {
                scanf("%lf %lf", &x, &y);
                printf("Property %d: This property will begin eroding in year %d.\n", i, years(x, y));
                n--;
                i++;
        }
        printf("END OF OUTPUT.\n");
        return 0;
}
