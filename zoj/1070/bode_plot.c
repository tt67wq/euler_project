/*
 * =====================================================================================
 *
 *       Filename:  bode_plot.c
 *
 *    Description:  zoj 1070
 *
 *        Version:  1.0
 *        Created:  2019-08-01
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

double VS, R, C, VR;
double w;

/* VR = CRw VS / sqrt (1+ (CRw) ^ 2 )) */

int main() {
        int i, n;

        while (scanf("%lf %lf %lf %d", &VS, &R, &C, &n) != EOF) {
                for (i = 0; i < n; i++) {
                        scanf("%lf", &w);
                        VR = (C * R * w * VS) / sqrt(1 + pow(C * R * w, 2));
                        printf("%.03lf\n", VR);
                }
        }
        return 0;
}
