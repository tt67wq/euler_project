/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-16
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535897932384626433832795028
#define DELTA 1e-4

double escape_rate(double x, double y) {
        double alpha = atan(x / (4 - y));
        double beta = atan(y / (3 - x));
        return (alpha + beta) / (2 * PI) + 0.25;
}

int main() {

        double x, y, rate_sum = 0.0;
        unsigned long counter = 0;

        for (x = DELTA; x < 3; x += DELTA) {
                double h = 4 - x * 4 / 3;
                for (y = DELTA; y < h; y += DELTA) {
                        rate_sum += escape_rate(x, y);
                        counter++;
                }
        }
        printf("%.10f, %lu\n", rate_sum, counter);
        printf("%.10f\n", rate_sum / counter);
        // 0.3916721504

        return 0;
}