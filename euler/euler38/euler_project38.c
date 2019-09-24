/*
 * =====================================================================================
 *
 *       Filename:  euler_project38.c
 *
 *    Description:  欧拉计划第38题
 *
 *        Version:  1.0
 *        Created:  2018-09-05
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

#define LIMIT 999999999

int num_length(int num) {
        int l = 0;
        while (num) {
                l++;
                num /= 10;
        }
        return l;
}

long generate_num(int start) {
        long num = 0;
        int index = 1;
        while (1) {
                long tmp = start * index++;
                long next = num * (long)pow(10, num_length(tmp)) + tmp;
                if (next > LIMIT)
                        break;
                else
                        num = next;
        }
        return num;
}

int check(long num) {
        int digits[9] = {0};
        while (num) {
                if (digits[num % 10 - 1] == 1)
                        return 0;
                digits[num % 10 - 1] = 1;
                num /= 10;
        }
        for (int i = 0; i < 9; i++)
                if (digits[i] == 0)
                        return 0;
        return 1;
}

int main() {
	clock_t begin = clock();
        long mx = 0;
        for (int i = 90; i < 99; i++) {
                int tmp = generate_num(i);
                if (check(tmp)) {
                        printf("%d\n", tmp);
                        mx = mx > tmp ? mx : tmp;
                }
        }
        for (int i = 910; i < 999; i++) {
                int tmp = generate_num(i);
                if (check(tmp)) {
                        printf("%d\n", tmp);
                        mx = mx > tmp ? mx : tmp;
                }
        }
        for (int i = 9100; i < 9999; i++) {
                int tmp = generate_num(i);
                if (check(tmp)) {
                        printf("%d\n", tmp);
                        mx = mx > tmp ? mx : tmp;
                }
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %ld time use => %lfs\n", mx, (double)(timespent / CLOCKS_PER_SEC));

        exit(EXIT_SUCCESS);
}
