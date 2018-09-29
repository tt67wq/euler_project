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

typedef unsigned long long ull;

int gcd(int m, int n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int multis_by1(int num, int (*ms)[2]) {
        int index = 1;
        for (int a = 0; a < 10; a++) {
                for (int b = 0; b < 10; b++)
                        if (pow(5, a) * pow(2, b) == num) {
                                if (a == 0 || b == 0)
                                        continue;
                                else {
                                        ms[index][0] = (int)pow(2, b);
                                        ms[index][1] = (int)pow(5, a);
                                        index++;
                                }
                        }
        }
        ms[0][0] = 1;
        ms[0][1] = num;
        return index;
}

void factorize(ull num, int (*facs)[2]) {
        int i;
        int index = 0;
        for (i = 2; i <= num; i++) {
                if (num % i == 0) {
                        num /= i;
                        int exists = 0;
                        for (int j = 0; j < index; j++) {
                                if (facs[j][0] == i) {
                                        facs[j][1]++;
                                        exists = 1;
                                        break;
                                }
                        }
                        if (!exists) {
                                facs[index][0] = i;
                                facs[index][1] = 1;
                                index++;
                        }
                        i--;
                }
        }
}

int multis_by2(ull num) {
        int facs[10][2] = {{0}};
        int ps = 1;
        factorize(num, facs);
        for (int i = 0; i < 10; i++) {
                /* printf("%d ==> %d\n", facs[i][0], facs[i][1]); */
                if (facs[i][1] > 0)
                        ps *= (facs[i][1] + 1);
        }
        /* printf("%llu ==> %d\n", num, ps); */
        return ps;
}

int main() {
	clock_t begin = clock();
        int facs[100] = {
            1,         2,         4,         5,         8,        10,       16,        20,
            25,        32,        40,        50,        64,       80,       100,       125,
            128,       160,       200,       250,       256,      320,      400,       500,
            512,       625,       640,       800,       1000,     1250,     1280,      1600,
            2000,      2500,      2560,      3125,      3200,     4000,     5000,      6250,
            6400,      8000,      10000,     12500,     12800,    15625,    16000,     20000,
            25000,     31250,     32000,     40000,     50000,    62500,    64000,     78125,
            80000,     100000,    125000,    156250,    160000,   200000,   250000,    312500,
            320000,    390625,    400000,    500000,    625000,   781250,   800000,    1000000,
            1250000,   1562500,   1600000,   1953125,   2000000,  2500000,  3125000,   3906250,
            4000000,   5000000,   6250000,   7812500,   8000000,  10000000, 12500000,  15625000,
            20000000,  25000000,  31250000,  40000000,  50000000, 62500000, 100000000, 125000000,
            200000000, 250000000, 500000000, 1000000000};

        ull sum = 0;
        for (int x = 1; x < 10; x++) {
                int base = (int)pow(10, x);
                printf("%d, %d, sum => %llu\n", x, base, sum);
                for (int i = 0; i < 100; i++) {
                        if (facs[i] > base)
                                break;
                        if (base % facs[i] == 0) {
                                int ms[10][2] = {{0}};

                                int t = multis_by1(facs[i], ms);
                                for (int j = 0; j < t; j++) {
                                        int pk = (int)(base / facs[i]) * (ms[j][0] + ms[j][1]);
                                        ull s = multis_by2(pk);
                                        sum += s;
                                }
                        }
                }
        }

        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %llu time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));


        return 0;
}
