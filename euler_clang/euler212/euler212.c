/*
 * =====================================================================================
 *
 *       Filename:  euler212.c
 *
 *    Description:  欧拉计划212题
 *
 *        Version:  1.0
 *        Created:  2019-06-20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define N 300000l
#define M 50000

typedef unsigned long ul;

typedef struct _cube {
        int bp;
        ul x0, y0, z0;
        ul x1, y1, z1;
} cube;

ul fib_cache[N+1];

cube cubes[M + 1];
cube mcubes[100000];
int MSIZE = 0;
ul TOTAL_VOLUMN = 0;

void lagged_fibonacci() {
        for (int i = 1; i <= N; i++) {
                if (i < 56) {
                        fib_cache[i] = (100003l - 200003l * i + 300007l * i * i * i) % 1000000l;
                } else {
                        fib_cache[i] = (fib_cache[i - 24] + fib_cache[i - 55]) % 1000000l;
                }
        }
        return;
}

ul volume(cube a) { return (a.x1 - a.x0) * (a.y1 - a.y0) * (a.z1 - a.z0); }

void gene_cubes() {
        cube tmp;
        for (int i = 1; i <= M; i++) {
                tmp.bp = 0;
                tmp.x0 = fib_cache[6 * i - 5] % 10000;
                tmp.y0 = fib_cache[6 * i - 4] % 10000;
                tmp.z0 = fib_cache[6 * i - 3] % 10000;
                tmp.x1 = tmp.x0 + 1 + fib_cache[6 * i - 2] % 399;
                tmp.y1 = tmp.y0 + 1 + fib_cache[6 * i - 1] % 399;
                tmp.z1 = tmp.z0 + 1 + fib_cache[6 * i] % 399;
                cubes[i] = tmp;
                TOTAL_VOLUMN += volume(tmp);
        }
        return;
}

int join(cube a, cube b) {
        if (a.x0 >= b.x1 || a.x1 <= b.x0)
                return 0;
        if (a.y0 >= b.y1 || a.y1 <= b.y0)
                return 0;
        if (a.z0 >= b.z1 || a.z1 <= b.z0)
                return 0;
        return 1;
}

cube merge(cube a, cube b) {
        cube tmp;
        tmp.x0 = max(a.x0, b.x0);
        tmp.y0 = max(a.y0, b.y0);
        tmp.z0 = max(a.z0, b.z0);

        tmp.x1 = min(a.x1, b.x1);
        tmp.y1 = min(a.y1, b.y1);
        tmp.z1 = min(a.z1, b.z1);

        return tmp;
}

void pre() {
        int index = 0;
        for (int i = 1; i < M; i++) {
                for (int j = i + 1; j <= M; j++) {
                        if (join(cubes[i], cubes[j])) {
                                cube tmp = merge(cubes[i], cubes[j]);
                                tmp.bp = j;
                                mcubes[index] = tmp;
                                index++;
                                TOTAL_VOLUMN -= volume(tmp);
                        }
                }
        }
        printf("level: 1, size: %d, volume: %lu\n", index, TOTAL_VOLUMN);
        MSIZE = index;
        return;
}

void iter() {
        int index = 0;
        int flag = 1;
        int level = 2;
        cube buffer[MSIZE];
        while (MSIZE) {
                for (int i = 0; i < MSIZE; i++) {
                        cube a = mcubes[i];
                        for (int j = a.bp + 1; j <= M; j++) {
                                if (join(cubes[j], a)) {
                                        cube tmp = merge(cubes[j], a);
                                        tmp.bp = j;
                                        buffer[index] = tmp;
                                        index++;
                                        TOTAL_VOLUMN += flag * volume(tmp);
                                }
                        }
                }
                printf("level: %d, size: %d, volume: %lu\n", level, index, TOTAL_VOLUMN);
                MSIZE = index;
                index = 0;
                memcpy(mcubes, buffer, sizeof(cube) * (MSIZE));
                flag = flag * -1;
                level++;
        }
        return;
}

int main(int argc, const char *argv[]) {
        lagged_fibonacci();
        gene_cubes();
        pre();
        iter();

        printf("%lu\n", TOTAL_VOLUMN);

        return 0;
}
