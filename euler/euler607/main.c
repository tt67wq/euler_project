/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-11-02
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SQRT2 sqrt(2)

const int SPEED[] = {10, 9, 8, 7, 6, 5, 10};
const int NUM_ITERATION = 10000;

struct _Point {
        double x;
        double y;
};
typedef struct _Point Point;

double distance(Point a, Point b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
}

double duration(Point *points) {
        double res = 0;
        for (int i = 0; i < 7; i++) {
                double d = distance(points[i], points[i + 1]);
                res += (d / SPEED[i]);
        }
        return res;
}

uint32_t myrand() {
        static uint64_t seed = 0;
        seed = 6364136223846793005ULL * seed + 1;
        return (uint32_t)(seed >> 30);
}

void mutate(Point *points, double delta) {
        double od = duration(points);

        if (myrand() & 1) {
                delta = -delta;
        }

        int id = myrand() % 6 + 1;
        points[id].y += delta;

        if (duration(points) >= od) {
                points[id].y -= delta;
        }
}

int main() {
        Point points[8] = {};

        // A
        points[0].x = 0;
        points[0].y = 0;

        // B
        points[7].x = 100 / SQRT2;
        points[7].y = 100 / SQRT2;

        points[1].x = 50 / SQRT2 - 25;
        points[1].y = 50 / SQRT2 - 25;

        for (int i = 2; i < 7; i++) {
                points[i].x = points[i - 1].x + 10;
                points[i].y = points[i - 1].y + 10;
        }

        printf("direct line cost => %f\n", duration(points));

        for (double delta = 0.1; delta > 0.000001; delta /= 10) {
                for (int i = 0; i < NUM_ITERATION; i++) {
                        mutate(points, delta);
                }
        }

        printf("least line cost => %0.10f\n", duration(points));

        return 0;
}