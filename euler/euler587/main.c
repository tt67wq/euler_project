/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-10-09
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

#define CIRCLE(x) (1 - sqrt(1 - ((x)-1) * ((x)-1)))

double EPSILON = 0.0000000001;
int STEPS = 1000000;

// get cross point of  `slope * x = 1 - sqrt(1-(x-1)*(x-1))`
double getIntersection(double slope) {
        double x = 0.5;
        double step = 0.1;

        while (1) {
                double leftSide = slope * x;
                double rightSide = CIRCLE(x);

                // close enough
                if (fabs(leftSide - rightSide) < EPSILON) {
                        return x;
                }

                // mv x
                if (leftSide > rightSide) {
                        x -= step;
                } else {
                        x += step;
                }

                // step smaller
                step *= 0.99;
        }
}

double getAreaL(double slope) {
        double intersection = 0;
        double leftArea = 0;
        if (slope > 0) {
                intersection = getIntersection(slope);
                leftArea = intersection * (intersection * slope) / 2;
        }

        double rightArea = 0;
        double step = (1 - intersection) / STEPS;

        // integral
        for (double x = intersection; x < 1; x += step) {
                double y = CIRCLE(x);
                rightArea += y * step;
        }
        return leftArea + rightArea;
}

int main() {
        double limit = 0.001;
        int numCircles = 1;
        int step = 64;

        double L = getAreaL(0);
        while (1) {
                double slope = (double)1.0 / numCircles;
                double area = getAreaL(slope);
                if (area / L < limit) {
                        if (step == 1) {
                                break;
                        }
                        numCircles -= step;
                        step /= 2;
                } else {
                        numCircles += step;
                }
        }

        printf("%d\n", numCircles);
        return 0;
}