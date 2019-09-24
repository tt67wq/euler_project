/*
 * =====================================================================================
 *
 *       Filename:  euler_problem154.c
 *
 *    Description:  欧拉计划154题
 *
 *        Version:  1.0
 *        Created:  2018-08-20
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

#define LIMIT 200000

void factorial_count2(int num, int *count2) {
        int t = 0;
        int tmp = num;
        while (tmp % 2 == 0) {
                tmp /= 2;
                t++;
        }
        count2[num] = count2[num - 1] + t;
}

void factorial_count5(int num, int *count5) {
        int f = 0;
        int tmp = num;
        while (tmp % 5 == 0) {
                tmp /= 5;
                f++;
        }

        count5[num] = count5[num - 1] + f;
}

int no_reminder(int a, int b, int c, int *count2, int *count5) {
        int t, f;
        t = count2[a] + count2[b] + count2[c];
        f = count5[a] + count5[b] + count5[c];
        if (count2[LIMIT] - 12 >= t && count5[LIMIT] - 12 >= f)
                return 1;
        return 0;
}

int main() {

        int count2[LIMIT + 1] = {0};
        int count5[LIMIT + 1] = {0};
        for (int i = 2; i <= LIMIT; i++) {
                factorial_count2(i, count2);
                factorial_count5(i, count5);
        }

        unsigned long long sum = 0;
        for (int level = LIMIT; level >= 0; level--) {
                printf("%d ==> %llu\n", level, sum);
                for (int index = level; index >= 0; index--) {
                        if (no_reminder(index, LIMIT - level, level - index, count2, count5))
                                sum++;
                }
        }
        printf("%llu\n", sum);

        return 1;
}
