/*
 * =====================================================================================
 *
 *       Filename:  euler191.c
 *
 *    Description:  欧拉191题
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

#include "khash.h"
#include "kvec.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Ontime 1
#define Late 2
#define Absent 3
typedef kvec_t(int) array;
KHASH_MAP_INIT_STR(cache, uint64_t)

int kmp_index(array *s, int *t, int *next) {
        int i = 0;
        int j = 0;
        while (i < kv_size(*s) && j < 3) {

                if (j == -1 || s->a[i] == t[j]) {
                        i++;
                        j++;
                } else {
                        j = next[j];
                }
        }

        if (j >= 3)
                return (i - 3);
        return -1;
}

int check(array *vec) {
        // 3 consecutive absents or >=2 lates

        int lates = 0;
        for (int i = 0; i < kv_size(*vec); i++) {
                if (kv_A(*vec, i) == Late)
                        lates++;
                if (lates >= 2)
                        return 0;
        }

        // kmp
        int next[3] = {-1, 0, 1};
        int t[3] = {Absent, Absent, Absent};

        if (kmp_index(vec, t, next) != -1) {
                // match
                return 0;
        }

        return 1;
}

char *finger_print(array *vec) {
        char *finger = (char *)calloc(4, sizeof(char));
        finger[0] = kv_size(*vec) + '0';

        int has_late = 0;
        for (int i = 0; i < kv_size(*vec); i++) {
                if (kv_A(*vec, i) == Late) {
                        has_late++;
                        break;
                }
        }
        finger[1] = has_late + '0';
        finger[2] = kv_A(*vec, kv_size(*vec) - 2) + '0';
        finger[3] = kv_A(*vec, kv_size(*vec) - 1) + '0';
        return finger;
}

uint64_t dfs(array *vec, khash_t(cache) * h) {

        uint64_t result = 0;

        if (kv_size(*vec) == 30)
                return (uint64_t)check(vec);

        if (check(vec)) {
                /* search cache */
                char *finger;
                khiter_t k;

                if (kv_size(*vec) >= 2) {
                        finger = finger_print(vec);
                        k = kh_get(cache, h, finger);
                        if (k == kh_end(h)) {
                                // missing
                        } else {
                                return kh_val(h, k);
                        }
                }

                // still has chance to get reward
                for (int i = 1; i < 4; i++) {
                        kv_push(int, *vec, i);
                        result += dfs(vec, h);
                        kv_pop(*vec);
                }
                // cache
                if (kv_size(*vec) >= 2) {
                        int ret = 0;
                        k = kh_put(cache, h, finger, &ret);
                        kh_value(h, k) = result;
                }
        } else {
                // no chance
        }
        return result;
}

int main() {
        double dtime = clock();
        array vec;
        kv_init(vec);
        khash_t(cache) *h = kh_init(cache);
        dtime = (double)(clock() - dtime) / CLOCKS_PER_SEC;
        printf("%llu\n", dfs(&vec, h));
        printf("time=%.6lf sec.\n", dtime);
        kv_destroy(vec);
        kh_destroy(cache, h);
        return 0;
}
