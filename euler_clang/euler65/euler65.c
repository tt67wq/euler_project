/*
 * =====================================================================================
 *
 *       Filename:  euler65.c
 *
 *    Description:  欧拉计划65题
 *
 *        Version:  1.0
 *        Created:  2019-04-09
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

typedef kvec_t(uint64_t) array;

uint64_t get_an(int n) {
        if (n == 0)
                return 2;
        int d = n / 3;
        int r = n % 3;

        if (r == 1 || r == 0)
                return 1;
        return (d + 1) << 1;
}

int digits_sum(uint64_t n) {
        int s = 0;
        while (n) {
                s += n % 10;
                n /= 10;
        }
        return s;
}

void count2n(array *h, array *k, int n, int index) {
        if (index == n)
                return;
        uint64_t an = get_an(index);
        uint64_t nh, nk;
        if (index == 0) {
                nh = an;
                nk = 1;
        } else if (index == 1) {
                nh = an * kv_A(*h, 0) + 1;
                nk = an * kv_A(*k, 0);
        } else {
                nh = kv_A(*h, index - 1) * an + kv_A(*h, index - 2);
                nk = kv_A(*k, index - 1) * an + kv_A(*k, index - 2);
        }
        kv_push(uint64_t, *h, nh);
        kv_push(uint64_t, *k, nk);
        count2n(h, k, n, ++index);
}

int main() {
        array h, k;
        kv_init(h);
        kv_init(k);
        count2n(&h, &k, 100, 0);
        printf("%d\n", digits_sum(kv_A(h, kv_size(h) - 1)));
        return 1;
}
