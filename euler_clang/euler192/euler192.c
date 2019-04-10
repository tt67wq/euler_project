/*
 * =====================================================================================
 *
 *       Filename:  euler192.c
 *
 *    Description:  欧拉计划192题
 *
 *        Version:  1.0
 *        Created:  2019-04-10
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
typedef kvec_t(uint64_t) list;

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
        k -= 1;
        int na = nb * k - a;
        item t = {a, b, k};
        kv_push(item, *vec, t);
        continued_fraction(n, na, nb, vec);
}

int get_an(int n, array *vec) {
        if (n == 0)
                return kv_A(*vec, 0).a;
        return kv_A(*vec, n % kv_size(*vec)).k;
}

void count_util(list *h, list *k, array *vec, int index) {
        uint64_t an = (uint64_t)get_an(index, vec);
        uint64_t nh, nk;
        if (index == 0) {
                nh = an;
                nk = 1;
        } else if (index == 1) {
                nh = an * kv_A(*h, 0) + 1;
                nk = an * kv_A(*k, 0);
        } else {
                nh = an * kv_A(*h, index - 1) + kv_A(*h, index - 2);
                nk = an * kv_A(*k, index - 1) + kv_A(*k, index - 2);
        }
        if (nk > 10000)
                return;

        kv_push(uint64_t, *h, nh);
        kv_push(uint64_t, *k, nk);
        count_util(h, k, vec, index + 1);
}

uint64_t gcd(uint64_t m, uint64_t n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

int main() {
        array vec;
        list h, k;
        kv_init(vec);
        kv_init(h);
        kv_init(k);
        continued_fraction(13, nearest_sqrt(13), 1, &vec);
        for (int i = 0; i < kv_size(vec); i++)
                printf("%d ", kv_A(vec, i).k);
        printf("\n");
        count_util(&h, &k, &vec, 0);
        for (int i = 0; i < kv_size(h); i++) {
                uint64_t m = kv_A(h, i);
                uint64_t n = kv_A(k, i);
                /* uint64_t g = gcd(m, n); */
                printf("%llu/%llu\n", m, n);
        }
        return 0;
}
