/*
 * =====================================================================================
 *
 *       Filename:  euler215.c
 *
 *    Description:  欧拉计划215题
 *
 *        Version:  1.0
 *        Created:  2019-06-28
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

/* #define W 9 */
/* #define H 3 */
/* #define MAX 5 */
#define W 32
#define H 10
#define MAX 3329

typedef kvec_t(char) array;
typedef kvec_t(array) list;
typedef unsigned long ul;

char LB = 3; // long brick
char SB = 2; // short brick
char MATCH[MAX][MAX] = {{0}};
ul CACHE[MAX][H] = {{0}};

int length(array *row) {
        int sum = 0;
        for (int i = 0; i < kv_size(*row); i++) {
                sum += (int)kv_A(*row, i);
        }
        return sum;
}

// 生成满足长度的行
void gen_rows(array *r, list *l) {
        int len = length(r);

        // accept
        if (len == W) {
                array tmp;
                kv_init(tmp);

                for (int i = 0; i < kv_size(*r); i++)
                        kv_push(char, tmp, kv_A(*r, i));

                kv_push(array, *l, tmp);
                return;
        }

        // drop
        if (len > W)
                return;

        kv_push(char, *r, LB);
        gen_rows(r, l);
        kv_pop(*r);

        kv_push(char, *r, SB);
        gen_rows(r, l);
        kv_pop(*r);

        return;
}

// 检查有没有裂缝
char is_stable(array r1, array r2) {
        int p1 = (int)kv_A(r1, 0);
        int p2 = (int)kv_A(r2, 0);
        int i = 1, j = 1;

        while (p1 != p2) {
                if (p1 > p2) {
                        p2 += (int)kv_A(r2, j);
                        j++;
                } else {
                        p1 += (int)kv_A(r1, i);
                        i++;
                }
        }
        if (p1 == W)
                return 1;
        return 0;
}

void print_row(array *r) {
        for (int i = 0; i < kv_size(*r); i++)
                printf("%d ", kv_A(*r, i));
}

ul dfs(int level, int state) {
        if (CACHE[state][level])
                return CACHE[state][level];
        if (level + 1 == H)
                return 1;
        ul res = 0;
        for (int i = 0; i < MAX; i++) {
                if (i == state)
                        continue;
                if (MATCH[state][i])
                        res += dfs(level + 1, i);
        }
        CACHE[state][level] = res;
        return res;
}

int main(int argc, const char *argv[]) {
        array r;
        list l;
        kv_init(r);
        kv_init(l);

        gen_rows(&r, &l);

        printf("total rows: %ld\n", kv_size(l));
        for (int i = 0; i < kv_size(l); i++) {
                for (int j = 0; j < kv_size(l); j++) {
                        if (i == j)
                                continue;
                        array r1 = kv_A(l, i);
                        array r2 = kv_A(l, j);
                        if (is_stable(r1, r2))
                                MATCH[i][j] = 1;
                }
        }

        ul res = 0;
        for (int i = 0; i < kv_size(l); i++) {
                ul tmp = dfs(0, i);
                printf("line %d = %ld\n", i, tmp);
                res += tmp;
        }

        printf("%ld\n", res);

        return 0;
}
