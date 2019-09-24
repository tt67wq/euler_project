/*
 * =====================================================================================
 *
 *       Filename:  bigint.c
 *
 *    Description:  大数库
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

bigint new_bigint_from_int(int n) {
        bigint c;
        kv_init(c);
        while (n) {
                kv_push(int, c, n % 10);
                n /= 10;
        }
        return c;
}

bigint new_bigint_from_char(char *s) {
        bigint c;
        kv_init(c);
        for (int i = strlen(s) - 1; i >= 0; i--)
                kv_push(int, c, *(s + i) - '0');
        return c;
}

void print_bigint(bigint n) {
        for (int i = kv_size(n) - 1; i >= 0; i--)
                printf("%d", kv_A(n, i));
        printf("\n");
}

bigint add(bigint a, bigint b) {
        bigint c;
        kv_init(c);
        int l = kv_size(a) > kv_size(b) ? kv_size(a) : kv_size(b);
        int x, y, sum, prev = 0;
        for (int i = 0; i < l; i++) {
                x = kv_size(a) > i ? kv_A(a, i) : 0;
                y = kv_size(b) > i ? kv_A(b, i) : 0;
                sum = x + y + prev;
                kv_push(int, c, sum > 9 ? sum - 10 : sum);
                prev = sum > 9 ? 1 : 0;
        }

        if (prev)
                kv_push(int, c, 1);

        return c;
}

bigint _multiply(bigint m, int n) {
        bigint t;
        kv_init(t);

        int tmp, prev = 0;

        for (int i = 0; i < kv_size(m); i++) {
                tmp = kv_A(m, i) * n + prev;
                kv_push(int, t, tmp % 10);
                prev = tmp / 10;
        }
        if (prev)
                kv_push(int, t, prev);
        return t;
}

void reverse(bigint *n) {
        for (int i = 0; i < kv_size(*n) / 2; i++) {
                int tmp = kv_A(*n, i);
                n->a[i] = n->a[kv_size(*n) - i - 1];
                n->a[kv_size(*n) - i - 1] = tmp;
        }
}

void add_zero(bigint *n, int m) {
        reverse(n);
        for (int i = 0; i < m; i++)
                kv_push(int, *n, 0);
        reverse(n);
}

bigint multiply(bigint m, bigint n) {
        bigint res = new_bigint_from_int(0);
        for (int i = 0; i < kv_size(n); i++) {
                bigint tmp = _multiply(m, kv_A(n, i));
                add_zero(&tmp, i);
                res = add(res, tmp);
                kv_destroy(tmp);
        }
        return res;
}
