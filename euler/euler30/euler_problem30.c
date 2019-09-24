/*
 * =====================================================================================
 *
 *       Filename:  euler_problem30.c
 *
 *    Description:  欧拉计划30题
 *
 *        Version:  1.0
 *        Created:  2018-08-16
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

#define LIMIT 354294

int fifth_power_digits(int num) {
        int sum = 0;
        while (num > 0) {
                sum += (int)pow(num % 10, 5);
                num /= 10;
        }
        return sum;
}

int main() {
        int sum = 0;
	clock_t begin = clock();
        for (int i = 2; i < LIMIT; i++) {
                int s = fifth_power_digits(i);
                if (i == s) {
                        printf("%d => %d\n", i, i - s);
                        sum += i;
                }
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
