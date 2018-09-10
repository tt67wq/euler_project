/*
 * =====================================================================================
 *
 *       Filename:  euler_problem40.c
 *
 *    Description:  欧拉计划40题
 *
 *        Version:  1.0
 *        Created:  2018-09-10
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

int num_len(int num) {
        int len = 0;
        while (num) {
                len++;
                num /= 10;
        }
        return len;
}

int get_offset(int num, int offset) {
        int len = num_len(num);
        while (offset) {
                num %= (int)pow(10, len - 1);
                offset--;
                len--;
        }
        return (int)(num / pow(10, len - 1));
}

int main() {
        clock_t begin = clock();
        int sindex = 1;
        int eindex = 1;
        int anchors[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};
        int product = 1;
        int j = 0;
        for (int i = 1; i < 1000000; i++) {
                if (sindex > 1000000)
                        break;
                eindex = sindex + num_len(i);
                if (anchors[j] >= sindex && anchors[j] < eindex) {
                        int offset = anchors[j] - sindex;
                        int offset_digit = get_offset(i, offset);
                        printf("[%d, %d): %d, offset: %d, offset digits: %d\n", sindex, eindex, i,
                               offset, offset_digit);
                        product *= offset_digit;
                        j++;
                }

                sindex = eindex;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d, time use => %lfs\n", product, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
