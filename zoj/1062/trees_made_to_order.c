/*
 * =====================================================================================
 *
 *       Filename:  trees_made_to_order.c
 *
 *    Description:  zoj 1062
 *
 *        Version:  1.0
 *        Created:  2019-08-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

long ctl[30];
long dtl[30];

void init() {
        int i, j;
        ctl[0] = ctl[1] = 1;
        dtl[0] = 1;
        dtl[1] = 2;
        for (i = 2; i < 30; i++) {
                ctl[i] = 0;
                for (j = 0; j < i; j++)
                        ctl[i] = ctl[i] + ctl[j] * ctl[i - j - 1];
                dtl[i] = dtl[i - 1] + ctl[i];
        }
}

int nums(long n) {
        int i = 0;
        while (n >= dtl[i])
                i++;
        return i;
}

long min_by(int n) { return dtl[n - 1]; }

void print_tree(long n) {
        if (n == 1) {
                printf("X");
                return;
        }
        if (n == 2) {
                printf("X(X)");
                return;
        }

        int i, x, y, nx, ny;
        long d;

        i = nums(n);
        d = n - min_by(i);
        x = 0;
        y = i - 1;
        while (d > 0) {
                d -= ctl[x] * ctl[y];
                if (d < 0)
                        break;
                x++;
                y--;
        }
        if (d < 0) {
                d += ctl[x] * ctl[y];
        }
        nx = d / ctl[y];
        ny = d % ctl[y];

        if (x > 0) {
                printf("(");
                print_tree(min_by(x) + (long)nx);
                printf(")");
        }
        printf("X");
        if (y > 0) {
                printf("(");
                print_tree(min_by(y) + (long)ny);
                printf(")");
        }
}

int main() {
        init();
        long n;
        while (scanf("%ld", &n) != EOF) {
                if (n == 0)
                        break;
                print_tree(n);
                printf("\n");
        }

        return 0;
}
