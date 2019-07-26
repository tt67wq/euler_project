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

double vs[1000][2];
double res;
int num;

double cross(int a, int b, int c) { return (vs[b][0] - vs[a][0]) * (vs[c][1] - vs[a][1]) - (vs[c][0] - vs[a][0]) * (vs[b][1] - vs[a][1]); }

int solve() {
        int i, j, tmp;
        double p1, p2, p3, p4;
        res = 0.0;
        if (num < 3)
                return 0;

        for (i = 0; i < num; i++) {
                for (j = (i + 1) / num; j < i - 1; j++) {
                        tmp = (i + 1) % num;
                        p1 = cross(i, j, tmp);
                        p2 = cross(i, j + 1, tmp);
                        p3 = cross(j, i, j + 1);
                        p4 = cross(j, tmp, j + 1);
                        if (p1 * p2 <= 0 && p3 * p4 <= 0)
                                return 0;
                }
        }

        /* area */
        for (i = 0; i < num; i++) {
                tmp = (i + 1) % num;
                res += vs[i][0] * vs[tmp][1] - vs[i][1] * vs[tmp][0];
        }

        res = res > 0 ? res : -res;
        res /= 2;
        return 1;
}

int main() {
        int count = 0;
        int i;
        while (scanf("%d", &num) != EOF) {
                if (!num)
                        break;
                ++count;
                if (count > 1)
                        printf("\n");
                for (i = 0; i < num; i++)
                        scanf("%lf %lf", &vs[i][0], &vs[i][1]);

                if (solve())
                        printf("Figure %d: %.2lf\n", count, res);
                else
                        printf("Figure %d: Impossible\n", count);
        }
        return 0;
}
