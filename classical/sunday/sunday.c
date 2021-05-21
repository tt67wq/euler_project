/*
 * =====================================================================================
 *
 *       Filename:  sunday.c
 *
 *    Description:  sunday算法
 *
 *        Version:  1.0
 *        Created:  2019-07-22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 1024

int sunday(const char *src, const char *des) {
        int shift[NUM];
        int len_d = strlen(des);
        int len_s = strlen(src);
        int p, k, j;
        int pos = 0;
        int end = len_s - len_d;

        for (p = 0; p < NUM; p++)
                shift[p] = len_d + 1;

        for (k = 0; k < len_d; k++)
                shift[(int)des[k]] = len_d - k;

        while (pos <= end) {
                j = 0;
                while (src[pos + j] == des[j]) {
                        j++;
                        if (j >= len_d)
                                return pos;
                }
                pos += shift[(int)src[pos + len_d]];
        }
        return -1;
}

int main() {
        char src[] = "ajdiasujfaskjdaskdaskujashjd";
        char des[] = "skjdas";
        int pos;
        pos = sunday(src, des);
        printf("pos is %d\n", pos);
        return 0;
}
