/*
 * =====================================================================================
 *
 *       Filename:  stern_brocot.c
 *
 *    Description:  Stern-Brocot树
 *
 *        Version:  1.0
 *        Created:  2019-04-29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include "kvec.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Fraction {
        uint64_t n; // 分母
        uint64_t m; // 分子
};

typedef kvec_t(struct Fraction) array;

uint64_t gcd(uint64_t m, uint64_t n) {
        int r;
        if (m <= 0 || n <= 0)
                return 0;
        r = m % n;
        return r > 0 ? gcd(n, r) : n;
}

uint64_t level_num(int level) {
        if (!level)
                return 2;
        if (level == 1)
                return 3;
        return level_num(level - 1) + (uint64_t)pow(2, level - 1);
}

void stern_brocot_level(int level, array *fs) {
        uint64_t nums = level_num(level);
        kv_resize(struct Fraction, *fs, nums);

        // init
        for (int i = 0; i < nums; i++) {
                fs->a[i].m = 0;
                fs->a[i].n = 0;
        }

        fs->a[0].m = 1;
        fs->a[0].n = 0;

        fs->a[nums - 1].m = 0;
        fs->a[nums - 1].n = 1;

        int step = (nums - 1) / 2;
        while (step) {
                for (int i = step; i < nums; i += step) {
                        if (fs->a[i].m == 0 && fs->a[i].n == 0) {
                                uint64_t m = fs->a[i - step].m + fs->a[i + step].m;
                                uint64_t n = fs->a[i - step].n + fs->a[i + step].n;
                                uint64_t g = gcd(m, n);
                                fs->a[i].m = m / g;
                                fs->a[i].n = n / g;
                        }
                }
                step /= 2;
        }
        return;
}

int main(int argc, const char *argv[]) {
        int level = 0;
        level = atoi(argv[1]);
        printf("level nums -> %llu\n", level_num(level));

        array fs;
        kv_init(fs);

        stern_brocot_level(level, &fs);

        for (int i = 0; i < kv_max(fs); i++) {
                printf("%llu/%llu ", kv_A(fs, i).n, kv_A(fs, i).m);
        }
        printf("\n");
        return 0;
}
