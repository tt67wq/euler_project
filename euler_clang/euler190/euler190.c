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
#define T0 50000.0   // 初始温度
#define T_end (1e-8) // 最终温度
#define Delta (1e-6) // 最小调整步长
#define q 0.98       // 退火系数
#define L 10000      // 每个温度的迭代次数
#define K 1e10       // 差值接受参数

/* 371048281 */

// 计算pm
float log_pm(array *list) {
        double pm = 0.0;
        for (int i = 0; i < kv_size(*list); i++) {
                pm += (double)(i + 1) * log(kv_A(*list, i));
        }
        return pm;
}

// 变异
void change(array *list) {
        int pos1 = 0;
        int pos2 = 0;

        double r1 = ((double)rand()) / (RAND_MAX + 1.0);
        double r2 = ((double)rand()) / (RAND_MAX + 1.0);

        pos1 = (int)(kv_size(*list) * r1); // 第一个变异点位置
        pos2 = (int)(kv_size(*list) * r2); // 第二个变异点位置

        list->a[pos1] += Delta;
        list->a[pos2] -= Delta;
}

// 模拟退火
int get_biggest_pm(int size) {
        srand((unsigned)time(NULL)); // 随机种子
        double r, T;

        T = T0;
        array vec;
        array vec_copy;
        kv_init(vec);
        kv_init(vec_copy);

        // init
        for (int i = 0; i < size; i++) {
                kv_push(double, vec, 1.0);
        }

        while (T > T_end) {

                for (int i = 0; i < L; i++) {
                        // copy
                        kv_copy(double, vec_copy, vec);
                        // change
                        change(&vec);
                        double df = log_pm(&vec) - log_pm(&vec_copy);

                        if (df <= 0.0) { // worse
                                r = ((double)rand()) / (RAND_MAX);
                                /* double p = 1 / (1 + exp(df / T)); */
                                double p = exp(df * K / T);
                                if (p < r) {
                                        // rollback
                                        kv_copy(double, vec, vec_copy);
                                } else {
                                        // accept
                                }
                        }
                }
                T *= q;
        }

        for (int i = 0; i < kv_size(vec); i++) {
                printf("%f ", kv_A(vec, i));
        }
        printf("\n");

        double res = exp(log_pm(&vec));
        printf("res => %f\n", res);
        return floor(res);
}

int main() {
        /* int s = 0; */
        /* for (int i = 2; i < 16; i++) { */
        /*         s += get_biggest_pm(i); */
        /* } */
        /* printf("%d\n", s); */
        printf("%d\n", get_biggest_pm(10));
        return 0;
}
