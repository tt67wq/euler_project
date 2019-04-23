/*
 * =====================================================================================
 *
 *       Filename:  euler194.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-04-23
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
#include <string.h>
#include <time.h>

typedef kvec_t(int) array;


// 求N(25,75,1984)
// 令 a = N(1, 0, 1984) b = N(0, 1, 1984)
// N(25, 75, 1984) = a^25*b^75/C(100, 25)/6
int dfs(array *vec, int index, int colors) {
        int s = 0;
        if (index == 0) {
                // first
                for (int i = 0; i < colors; i++) {
                        kv_push(int, *vec, i);
                        s += dfs(vec, 1, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 1) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 0) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 2, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 2) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 0) == i || kv_A(*vec, 1) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 3, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 3) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 2) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 4, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 4) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 3) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 5, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 5) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 0) == i || kv_A(*vec, 4) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 6, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 6) {
                for (int i = 0; i < colors; i++) {
                        if (kv_A(*vec, 1) == i || kv_A(*vec, 4) == i)
                                continue;
                        kv_push(int, *vec, i);
                        s += dfs(vec, 7, colors);
                        kv_pop(*vec);
                }
        }
        if (index == 7)
                return 1;
        return s;
}

int main(int argc, const char *argv[]) {
        array vec;
        kv_init(vec);
        int colors = 0;
        colors = atoi(argv[1]);

        int s = dfs(&vec, 0, colors);
        printf("%d\n", s);
        return 0;
}
