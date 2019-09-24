
/*
 * =====================================================================================
 *
 *       Filename:  euler45.c
 *
 *    Description:  欧拉计划45题
 *
 *        Version:  1.0
 *        Created:  2018-10-10
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

#define MAXNUM 1000000

long long f1(int n) {
        long long t = n;
        return t * (t + 1) / 2;
}
long long f2(int n) {
        long long t = n;
        return t * (3 * t - 1) / 2;
}
long long f3(int n) {
        long long t = n;
        return t * (2 * t - 1);
}

int max(long long *data) {
        if (data[0] >= data[1] && data[0] >= data[2])
                return 0;

        if (data[1] >= data[0] && data[1] >= data[2])
                return 1;

        if (data[2] >= data[0] && data[2] >= data[1])
                return 2;
        return 0;
}

int min(long long *data) {
        if (data[0] <= data[1] && data[0] <= data[2])
                return 0;

        if (data[1] <= data[0] && data[1] <= data[2])
                return 1;

        if (data[2] <= data[0] && data[2] <= data[1])
                return 2;
        return 0;
}

void race(int *indexs, long long *datas) {
        int max_index = max(datas);
        int min_index = min(datas);

        if (max_index == min_index)
                return;

        if (min_index == 0) {
                indexs[0]++;
                datas[0] = f1(indexs[0]);
                race(indexs, datas);
        }

        if (min_index == 1) {
                indexs[1]++;
                datas[1] = f2(indexs[1]);
                race(indexs, datas);
        }
        if (min_index == 2) {
                indexs[2]++;
                datas[2] = f3(indexs[2]);
                race(indexs, datas);
        }
}

int main() {
        clock_t begin = clock();
        int indexs[3] = {285, 165, 144};
        long long datas[3] = {f1(285), f2(165), f3(144)};
        race(indexs, datas);
        long long res = datas[0];
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %lld time use => %lfs\n", res, (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
