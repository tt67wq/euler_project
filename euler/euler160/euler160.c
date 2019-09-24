/*
 * =====================================================================================
 *
 *       Filename:  euler160.c
 *
 *    Description:  欧拉计划160题
 *
 *        Version:  1.0
 *        Created:  2018-10-25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long ul;

ul g(ul x) {
        while (x % 10 == 0) {
                x /= 10;
        }
        return x % 100000;
}

ul f(ul x) {
        ul res = 1;
        ul index = 1;
        while (1) {
                if (index == x)
                        return res;
                res = g(res * g(index + 1));
                index++;
        }
}

int main() {
        clock_t begin = clock();
        ul res = f(1000000000000);
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %lu time use => %lfs\n", res, (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
