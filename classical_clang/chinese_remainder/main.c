/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-04-28
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

// 扩展欧几里得算法
int egcd(int a, int b) {
        int a1 = 0, a2 = 1, b1 = 1, b2 = 0;
        while (b != 0) {
                int c = a / b;
                int tmp = a;
                a = b;
                b = tmp % b;

                tmp = a1;
                a1 = a2 - c * a1;
                a2 = tmp;

                tmp = b1;
                b1 = b2 - c * b1;
                b2 = tmp;
        }
        return a2;
}

// 逆元
// ax = 1 mod b
int inverse(int a, int b) {
        int g = egcd(a, b);
        return g > 0 ? g : b + g;
}

// 中国剩余定理, 即解下面方程组
// x = b0 mod a0
// x = b1 mod a1
// x = b2 mod a2
// ...
// x = crt([[a0, b0], [a1, b1], [a2, b2]...])
int crt(int **pairs, int pairsSize) {
        int *ms = (int *)calloc(pairsSize, sizeof(int));
        int *rs = (int *)calloc(pairsSize, sizeof(int));
        int *mis = (int *)calloc(pairsSize, sizeof(int));
        int *ins = (int *)calloc(pairsSize, sizeof(int));

        for (int i = 0; i < pairsSize; i++) {
                ms[i] = pairs[i][0];
                rs[i] = pairs[i][1];
        }

        long product = 1;
        for (int i = 0; i < pairsSize; i++) {
                product *= ms[i];
        }

        for (int i = 0; i < pairsSize; i++) {
                mis[i] = product / ms[i];
                ins[i] = inverse(mis[i], ms[i]);
        }

        int ans = 0;
        for (int i = 0; i < pairsSize; i++) {
                ans += mis[i] * ins[i] * rs[i];
                ans %= product;
        }

        free(ms);
        free(rs);
        free(mis);
        free(ins);

        return ans;
}

int main() {
        int pair0[] = {3, 2};
        int pair1[] = {5, 3};
        int pair2[] = {7, 2};

        int *pairs[] = {pair0, pair1, pair2};

        printf("%d", crt(pairs, 3));
        return 0;
}
