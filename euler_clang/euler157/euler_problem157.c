/*
 * =====================================================================================
 *
 *       Filename:  euler_problem157.c
 *
 *    Description:  欧拉计划157题
 *
 *        Version:  1.0
 *        Created:  2018-08-30
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

int gcd(int m, int n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int multis_by1(int num, int (*ms)[2]) {
        int index = 0;
        for (int a = 1; a <= (int)sqrt(num); a++)
                for (int b = a; b <= num; b++) {
                        if (gcd(a, b) == 1 && a * b == num) {
                                ms[index][0] = a;
                                ms[index][1] = b;

                                index++;
                        }
                }
        return index;
}

int multis_by2(int num, int (*ps)[2], int *cache) {
        if (cache[num])
                return cache[num];
        int index = 0;
        for (int a = 1; a <= (int)sqrt(num); a++)
                for (int b = a; b <= num; b++) {
                        if (a * b > num)
                                break;
                        if (a * b == num) {
                                ps[index][0] = a;
                                ps[index][1] = b;
                                index++;
                                ps[index][0] = b;
                                ps[index][1] = a;
                                index++;
                        }
                }
        cache[num] = index;
        return index;
}

int count_by(int num, int *cache) {
        int ms[100][2] = {{0}};
        int sum = 0;
        int t = multis_by1(num, ms);
        for (int i = 0; i < t; i++) {
                int pk = 10 * (ms[i][0] + ms[i][1]) / (ms[i][0] * ms[i][1]);
                int ps[100][2] = {{0}};
                int s = multis_by2(pk, ps, cache);
                sum += s;
        }
        return sum;
}

int main() {
        int facs[99] = {
            1,         2,         4,        5,        8,        10,       16,        20,
            25,        32,        40,       50,       64,       80,       100,       125,
            128,       160,       200,      250,      256,      320,      400,       500,
            512,       625,       640,      800,      1000,     1250,     1280,      1600,
            2000,      2500,      2560,     3125,     3200,     4000,     5000,      6250,
            6400,      8000,      10000,    12500,    12800,    15625,    16000,     20000,
            25000,     31250,     32000,    40000,    50000,    62500,    64000,     78125,
            80000,     100000,    125000,   156250,   160000,   200000,   250000,    312500,
            320000,    390625,    400000,   500000,   625000,   781250,   800000,    1000000,
            1250000,   1562500,   1600000,  1953125,  2000000,  2500000,  3125000,   3906250,
            4000000,   5000000,   6250000,  7812500,  8000000,  10000000, 12500000,  15625000,
            20000000,  25000000,  31250000, 40000000, 50000000, 62500000, 100000000, 125000000,
            200000000, 250000000, 500000000};

        int cache[5000] = {0};
        for (int i = 0; i < 99; i++) {
                printf("%d:%d ==> %d\n", i, facs[i], count_by(facs[i], cache));
        }

        /* int sum = 0; */
        /* for (int x = 1; x < 10; x++) { */
        /*         int base = (int)pow(10, x); */
        /*         printf("%d\n", base); */
        /*         for (int i = 0; i < 99; i++) { */
        /*                 if (facs[i] > base) */
        /*                         break; */
        /*                 int fs = 0; */
        /*                 if (base % facs[i] == 0) { */
        /*                         int ms[100][2] = {{0}}; */

        /*                         int t = multis_by1(facs[i], ms); */
        /*                         for (int i = 0; i < t; i++) { */
        /*                                 int pk = */
        /*                                     10 * (ms[i][0] + ms[i][1]) / (ms[i][0] * ms[i][1]);
         */
        /*                                 int ps[100][2] = {{0}}; */
        /*                                 int s = multis_by2(pk, ps); */
        /*                                 fs += s; */
        /*                         } */
        /*                 } */
        /*         } */
        /* } */
        return 0;
}
