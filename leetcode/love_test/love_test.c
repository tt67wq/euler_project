/*
 * =====================================================================================
 *
 *       Filename:  love_test.c
 *
 *    Description:  从1..866278171的奇数中包含多少个数字3
 *
 *        Version:  1.0
 *        Created:  2019-04-12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 866278171

uint64_t bf_count(int top) {
        uint64_t counter = 0;
        for (int i = 1; i < top; i++) {
                if (i % 2) {
                        int t = i;
                        while (t) {
                                if (t % 10 == 3)
                                        counter += 1;
                                t /= 10;
                        }
                }
        }
        return counter;
}

uint64_t recursive_power(int m, int n) {
        uint64_t temp;

        if (n == 0) /* m^0 = 1                  */
                return 1;
        else if ((n & 0x01) == 0) { /* if power is even then */
                temp = recursive_power(m, n >> 1);
                return temp * temp; /* m^(2k) = (m^k)^2         */
        } else                      /* otherwise, m^n=m*m^(n-1) */
                return m * recursive_power(m, n - 1);
}

uint64_t fast_count(uint64_t top) {
        uint64_t counter = 0;
        int index = 0;
        uint64_t cache = 0;
        while (top) {
                uint64_t tmp = top % 10;
                if (index == 0)
                        counter += tmp > 3;
                else if (index == 1) {
                        counter += tmp;
                } else {
                        counter += tmp * 5 * (index + 1) * recursive_power(10, index - 2);
                }
                if (tmp > 3)
                        counter += recursive_power(10, index) / 2;
                if (tmp == 3)
                        counter += cache / 2;

                cache += recursive_power(10, index) * tmp;
                top /= 10;
                index += 1;
        }
        return counter;
}

int main(int argc, const char *argv[]) {
        printf("%llu\n", bf_count(54278));
        printf("%llu\n", fast_count(54278));
        printf("%llu\n", fast_count(N));
        return 1;
}
