/*
 * =====================================================================================
 *
 *       Filename:  gen_prime.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-01
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

typedef kvec_t(int) seq;

int main() {
        seq vec;
        kv_init(vec);
        kv_resize(int, vec, 10);
        kv_push(int, vec, 1);
        kv_push(int, vec, 2);
        printf("%d\n", kv_a(int, vec, 1));
        printf("%zu\n", kv_size(vec));
        return 0;
}
