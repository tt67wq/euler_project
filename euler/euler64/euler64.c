/*
 * =====================================================================================
 *
 *       Filename:  euler64.c
 *
 *    Description:  欧拉计划64题
 *
 *        Version:  1.0
 *        Created:  2019-04-08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Item {
        int a;
        int b;
        int k;
} item;

typedef kvec_t(item) array;

int nearest_sqrt(int n) {
        int i = 1;
        for (; i * i < n; i++)
                ;
        return i - 1;
}

void continued_fraction(int n, int a, int b, array *vec) {
        // check repeatation
        for (int i = 0; i < kv_size(*vec); i++) {
                if (kv_A(*vec, i).a == a && kv_A(*vec, i).b == b)
                        return;
        }

        int nb = (n - a * a) / b;
        int k = 1;
        for (; (k * nb - a) * (k * nb - a) < n; k++)
                ;
        k--;
        int na = nb * k - a;
        item t = {a, b, k};
        kv_push(item, *vec, t);
        continued_fraction(n, na, nb, vec);
}

int main() {
        clock_t begin = clock();
        int counter = 0;
        array vec;
        for (int i = 2; i < 10001; i++) {

                int is_sqrt = 0;
                for (int j = 2; j < 101; j++) {
                        if (j * j == i)
                                is_sqrt = 1;
                }
                if (!is_sqrt) {
                        kv_init(vec);
                        continued_fraction(i, nearest_sqrt(i), 1, &vec);
                        if (kv_size(vec) % 2 == 1)
                                counter++;
                }
        }
        printf("%d\n", counter);
        clock_t end = clock();
        double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
