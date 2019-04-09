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

#include "bigint.h"
#include "kvec.h"
#include <time.h>

typedef kvec_t(bigint) array;

bigint get_an(int n) {
        if (n == 0)
                return new_bigint_from_int(2);
        int d = n / 3;
        int r = n % 3;

        if (r == 1 || r == 0)
                return new_bigint_from_int(1);
        return new_bigint_from_int((d + 1) << 1);
}

int digits_sum(bigint n) {
        int s = 0;
        for (int i = 0; i < kv_size(n); i++)
                s += kv_A(n, i);
        return s;
}

void count2n(array *h, array *k, int n, int index) {
        if (index == n)
                return;
        bigint an = get_an(index);
        bigint nh, nk;
        if (index == 0) {
                nh = an;
                nk = new_bigint_from_int(1);
        } else if (index == 1) {
                nh = add(multiply(an, kv_A(*h, 0)), new_bigint_from_int(1));
                nk = multiply(an, kv_A(*k, 0));
        } else {
                nh = add(multiply(kv_A(*h, index - 1), an), kv_A(*h, index - 2));
                nk = add(multiply(kv_A(*k, index - 1), an), kv_A(*k, index - 2));
        }
        kv_push(bigint, *h, nh);
        kv_push(bigint, *k, nk);
        count2n(h, k, n, ++index);
}

int main() {
        clock_t begin = clock();
        array h, k;
        kv_init(h);
        kv_init(k);
        count2n(&h, &k, 100, 0);
        print_bigint(kv_A(h, 99));
        print_bigint(kv_A(k, 99));
        clock_t end = clock();
        double timespent = end - begin;

        printf("%d\n", digits_sum(kv_A(h, 99)));
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));
        return 1;
}
