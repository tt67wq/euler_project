/*
 * =====================================================================================
 *
 *       Filename:  area.c
 *
 *    Description:  zoj 1010
 *
 *        Version:  1.0
 *        Created:  2019-07-25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

float vs[2000];
float res;
int num;

int solve() {
        int i, j;
        res = 0;
        if (num < 3)
                return 0;
        for (i = 0; i < num; i++) {
                j = i << 1;
                res += vs[j] * vs[j + 3] - vs[j + 1] * vs[j + 2];
        }
        res /= 2;
        return 1;
}

int main() {
        int count = 1;
        int i;
        float x, y;
        while (scanf("%d", &num) != EOF) {
                if (!num)
                        break;
                for (i = 0; i < num; i++) {
                        scanf("%f %f", &x, &y);
                        vs[i * 2] = x;
                        vs[i * 2 + 1] = y;
                }
                if (solve())
                        printf("Figure %d: %f\n", count, res);
                else
                        printf("Figure %d: Impossible\n", count);
                ++count;
                printf("\n");
        }
        return 0;
}
