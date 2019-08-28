/*
 * =====================================================================================
 *
 *       Filename:  euler346.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-08-28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "khash.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M (long)1e12

KHASH_MAP_INIT_INT64(cache, long);

void solve() {
        khash_t(cache) *h = kh_init(cache);
	int r;
        long i, j;
        khiter_t k;
        long sum, ssum = 1;
        long count = 0;
        for (i = 2; i * i <= M; i++) {
                sum = 1;
                printf("%ld: ", i);
                for (j = 1; sum < M; j++) {
                        sum += (long)pow(i, j);
                        if (sum > i + 1 && sum < M) {
                                printf("%ld ", sum);
                                k = kh_get(cache, h, sum);
                                if (k == kh_end(h)) {
                                        k = kh_put(cache, h, sum, &r);
                                        kh_value(h, k) = 1;
                                        ssum += sum;
                                        count++;
                                }
                        }
                }
                printf("\n");
        }
        printf("%ld, %ld\n", count, ssum);
}

int main() {
        solve();
        return 0;
}
