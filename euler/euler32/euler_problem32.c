/*
 * =====================================================================================
 *
 *       Filename:  euler_problem32.c
 *
 *    Description:  欧拉计划32题
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

int pandigital(int num1, int num2, int num3) {
        int digits[10] = {0};
        int p = 1; // true
        while (num1 != 0) {
                if (digits[num1 % 10]) {
                        return 0;
                }
                digits[num1 % 10] = 1;
                num1 /= 10;
        }
        while (num2 != 0) {
                if (digits[num2 % 10]) {
                        return 0;
                }
                digits[num2 % 10] = 1;
                num2 /= 10;
        }
        while (num3 != 0) {
                if (digits[num3 % 10]) {
                        return 0;
                }
                digits[num3 % 10] = 1;
                num3 /= 10;
        }
        for (int i = 1; i < 10; i++) {
                /* printf("%d", digits[i]); */
                if (digits[i] == 0) {
                        p = 0;
                        break;
                }
        }
        return p;
}

int main() {
        clock_t begin = clock();
        int pans[20] = {0};
        int index = 0;
        // 3 * 2 = 4
        for (int num1 = 100; num1 < 1000; num1++) {
                for (int num2 = 10; num2 < 100; num2++) {
                        int num3 = num1 * num2;
                        if (num3 > 10000 || num3 < 1000)
                                continue;
                        if (pandigital(num1, num2, num3)) {
                                printf("%d * %d = %d\n", num1, num2, num3);
                                int exists = 0;
                                for (int i = 0; i < index; i++) {
                                        if (pans[i] == num3) {
                                                exists = 1;
                                                break;
                                        }
                                }
                                if (exists == 0)
                                        pans[index++] = num3;
                        }
                }
        }

	// 4 * 1 = 4
        for (int num1 = 1000; num1 < 10000; num1++) {
                for (int num2 = 1; num2 < 10; num2++) {
                        int num3 = num1 * num2;
                        if (num3 > 10000 || num3 < 1000)
                                continue;

                        if (pandigital(num1, num2, num3)) {
                                printf("%d * %d = %d\n", num1, num2, num3);
                                int exists = 0;
                                for (int i = 0; i < index; i++) {
                                        if (pans[i] == num3) {
                                                exists = 1;
                                                break;
                                        }
                                }
                                if (exists == 0)
                                        pans[index++] = num3;
                        }
                }
        }

        int sum = 0;
        for (int i = 0; i < index + 1; i++)
                sum += pans[i];
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", sum, (double)(timespent / CLOCKS_PER_SEC));
        
        return 1;
}
