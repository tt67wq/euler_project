/*
 * =====================================================================================
 *
 *       Filename:  euler_project25.c
 *
 *    Description:  欧拉计划25题
 *
 *        Version:  1.0
 *        Created:  2018-08-10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 1000

void add(int *a, int *b, int *c) {
        for (int i = 0; i < LIMIT; i++) {
                c[i] = a[i] + b[i];
        }
        for (int i = 0; i < LIMIT; i++) {
                if (c[i] >= 10) {
                        c[i] -= 10;
                        c[i + 1] += 1;
                }
        }
}

int main() {
        clock_t begin = clock();
        int a[LIMIT] = {0};
        int b[LIMIT] = {0};
        int c[LIMIT] = {0};
        int index = 2;

        a[0] = 1;
        b[0] = 1;

        while (1) {
                if (b[LIMIT - 1] > 0)
                        break;
                add(a, b, c);
                for (int i = 0; i < LIMIT; i++) {
                        a[i] = b[i];
                        b[i] = c[i];
                        c[i] = 0;
                }
                index++;
        }
        clock_t end = clock();
        double timespent = end - begin;

        printf("result => %d, time use => %lfs\n", index, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
