/*
 * =====================================================================================
 *
 *       Filename:  farey.c
 *
 *    Description:  farey序列
 *
 *        Version:  1.0
 *        Created:  2019-05-10
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
#include <time.h>

typedef struct frac {
        int n, m;
        double val;
} frac;

typedef kvec_t(frac) array;

int cmp(const void *a, const void *b) {
        return ((frac *)a)->val - ((frac *)b)->val > 0 ? 1 : -1; //由小到大排序
}

int gcd(int x, int y) {
        if (!x)
                return y;
        if (x < y) {
                return gcd(y % x, x);
        }
        return gcd(x % y, y);
}

void build(int limit, int a, int b, int x, int y, array *vec) {
        int p = a + x;
        int q = b + y;
        int tmp = gcd(p, q);
        p /= tmp;
        q /= tmp;

        if (q < limit) {
                build(limit, a, b, p, q, vec);
                frac tmp = {p, q, (double)p / q};
                kv_push(frac, *vec, tmp);
                build(limit, p, q, x, y, vec);
        }
}

int main(int argc, const char *argv[]) {
        int limit = 0;
        limit = atoi(argv[1]);

        array vec;
        kv_init(vec);
        frac v0 = {0, 1, 0.0};
        frac v1 = {1, 1, 1.0};
        kv_push(frac, vec, v0);
        kv_push(frac, vec, v1);

        build(limit, 0, 1, 1, 1, &vec);
        qsort(vec.a, (int)kv_size(vec), sizeof(vec.a[0]), cmp);

        printf("size = %zu\n", kv_size(vec));
        for (int i = 0; i < kv_size(vec); i++) {
                printf("%d/%d ", vec.a[i].n, vec.a[i].m);
        }
        printf("\n");
        return 0;
}
