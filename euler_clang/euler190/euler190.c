/*
 * =====================================================================================
 *
 *       Filename:  euler190.c
 *
 *    Description:  欧拉计划190
 *
 *        Version:  1.0
 *        Created:  2019-04-04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef kvec_t(double) array;
#define BeginDelta (1e-1) // 最大迭代步长
#define EndDelta (1e-6)   // 最小调整步长
#define L 1000            // 最大不变次数

// 计算pm
double log_pm(array *list) {
        double pm = 0.0;
        for (int i = 0; i < kv_size(*list); i++) {
                pm += (double)(i + 1) * log(kv_A(*list, i));
        }
        return pm;
}

// 变异
void change(array *list, double delta) {
        struct timespec time1 = {0, 0};
        clock_gettime(CLOCK_REALTIME, &time1);
        srand(time1.tv_nsec);

        int pos1 = 0;
        int pos2 = 0;
        while (pos1 == pos2) {
                double r1 = ((double)rand()) / (RAND_MAX);
                double r2 = ((double)rand()) / (RAND_MAX);

                pos1 = (int)(kv_size(*list) * r1); // 第一个变异点位置
                pos2 = (int)(kv_size(*list) * r2); // 第二个变异点位置
        }

        list->a[pos1] += delta;
        list->a[pos2] -= delta;
}

// 模拟退火
uint64_t get_biggest_pm(int size) {
        array vec;
        array vec_copy;
        kv_init(vec);
        kv_init(vec_copy);

        // init
        for (int i = 0; i < size; i++) {
                kv_push(double, vec, 1.0);
        }

        int no_change_times = 0;
        double delta = BeginDelta;
        while (delta > EndDelta) {

                if (no_change_times >= L) {
                        delta /= 10;
                        no_change_times = 0;
                }

                // copy
                kv_copy(double, vec_copy, vec);
                // change
                change(&vec, delta);
                double df = log_pm(&vec) - log_pm(&vec_copy);

                if (df < 0.0) {
                        // rollback
                        kv_copy(double, vec, vec_copy);
                        no_change_times++;
                } else if (df == 0.0) {
                        no_change_times++;
                } else {
                        // better
                        no_change_times = 0;
                }
        }

        double res = exp(log_pm(&vec));
        printf("res => %llu\n", (uint64_t)floor(res));
        return (uint64_t)floor(res);
}

int main() {
        clock_t begin = clock();
        uint64_t s = 0;
        for (int i = 2; i < 16; i++) {
                s += get_biggest_pm(i);
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("%llu\n", s);
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));

        return 0;
}
