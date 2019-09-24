/*
 * =====================================================================================
 *
 *       Filename:  euler189.c
 *
 *    Description:  欧拉计划189题
 *
 *        Version:  1.0
 *        Created:  2019-04-03
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

typedef kvec_t(int) array;
KHASH_MAP_INIT_STR(cache, uint64_t)

int get_level(array *res) {
        int i = 0;
        for (; i * i < kv_size(*res); i++) {
        }
        return i - 1;
}

// only boarder count
int *get_boarder(array *res) {
        int level = get_level(res);
        int *boarder = (int *)calloc(level + 1, sizeof(int));
        int j = 0;
        for (int i = level * level; i < kv_size(*res); i++) {
                if (i % 2 == level % 2) {
                        boarder[j] = kv_A(*res, i);
                        j++;
                }
        }
        if ((kv_size(*res) % 2) == (level % 2)) {
                boarder[j] = kv_A(*res, kv_size(*res) - 1);
                j++;
        }
        for (int i = kv_size(*res) - 2 * level; i < level * level; i++) {
                if (i % 2 == (level - 1) % 2) {
                        boarder[j] = kv_A(*res, i);
                        j++;
                }
        }
        return boarder;
}

char *finger_print(array *res) {
        int *boarder = get_boarder(res);
        int level = get_level(res);
        char *finger = (char *)calloc(level + 3, sizeof(char));
        finger[0] = kv_size(*res) + '0';
        finger[1] = ':';
        for (int i = 2; i < level + 3; i++) {
                finger[i] = boarder[i - 2] + '0';
        }
        return finger;
}

uint64_t dfs(array *res, khash_t(cache) * h) {

        char *finger = finger_print(res);
        // search cache
        khiter_t k = kh_get(cache, h, finger);
        if (k == kh_end(h)) {
                // missing
        } else {
                return kh_val(h, k);
        }

        int size = kv_size(*res);
        int ret = 0;

        uint64_t result = 0;
        if (size == 64)
                return 1;

        // decide the color range of size
        if (size == 0 || size == 1 || size == 4 || size == 9 || size == 16 || size == 25 || size == 36 || size == 49) {
                // each color is ok

                for (int i = 1; i < 4; i++) {
                        kv_push(int, *res, i);
                        result += dfs(res, h);
                        kv_pop(*res);
                }
                k = kh_put(cache, h, finger, &ret);
                kh_value(h, k) = result;
                return result;
        }
        int level = get_level(res);

        if ((size % 2) ^ (level % 2)) {
                int color1 = kv_a(int, *res, size - 2 * level);
                int color2 = kv_a(int, *res, size - 1);
                for (int i = 1; i < 4; i++) {
                        if (i == color1 || i == color2)
                                continue;
                        kv_push(int, *res, i);
                        result += dfs(res, h);
                        kv_pop(*res);
                }
        } else {
                int color1 = kv_a(int, *res, size - 1);
                for (int i = 1; i < 4; i++) {
                        if (i == color1)
                                continue;
                        kv_push(int, *res, i);
                        result += dfs(res, h);
                        kv_pop(*res);
                }
        }
        k = kh_put(cache, h, finger, &ret);
        kh_value(h, k) = result;
        return result;
}

int main() {
        double dtime = clock();
        array vec;
        kv_init(vec);
        kv_push(int, vec, 2);
        khash_t(cache) *h = kh_init(cache);
        uint64_t result = dfs(&vec, h);
        dtime = (double)(clock() - dtime) / CLOCKS_PER_SEC;

        printf("%llu\n", result * 3);

        printf("time=%.3lf sec.\n", dtime);
        return 1;
}
