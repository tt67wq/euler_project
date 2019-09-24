/*
 * =====================================================================================
 *
 *       Filename:  euler_problem14.c
 *
 *    Description:  欧拉计划14题
 *
 *        Version:  1.0
 *        Created:  2018-07-24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 考拉兹序列
int collatz(long n, int *jump) {
        int size = 0;
        while (1) {
                size++;
                if (n == 1) {
                        break;
                } else if (n % 2 == 0) {
                        n = n >> 1;
                        if (n < 1000000 && jump[n] == 0)
                                jump[n] = 1;
                } else {
                        n = n * 3 + 1;
                        if (n < 1000000 && jump[n] == 0)
                                jump[n] = 1;
                }
        }
        return size;
}

int main() {
        clock_t begin = clock();
        long n = 13;
        int longest_seq = 0;
        long longest_seq_num = 0;
        int size;
        int jump_list[1000000] = {0};

        while (n < 1000000) {
                int exists = 0;

                if (jump_list[n] == 1)
                        exists = 1;

                if (exists == 0) {
                        size = collatz(n, jump_list);
                        if (size > longest_seq) {
                                longest_seq_num = n;
                                longest_seq = size;
                        }
                }
                n++;
        }
        clock_t end = clock();
        double timespent = end - begin;

        printf("result is %ld, longest seq is %d, time spend: %lfs\n", longest_seq_num, longest_seq, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
