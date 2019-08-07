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

long clt[30];
long dlt[30];

void init() {
        int i, j;
        clt[0] = clt[1] = 1;
        dlt[0] = 1;
        dlt[1] = 2;
        for (i = 2; i < 30; i++) {
                clt[i] = 0;
                for (j = 0; j < i; j++)
                        clt[i] = clt[i] + clt[j] * clt[i - j - 1];
                dlt[i] = dlt[i - 1] + clt[i];
        }
}

/* 1 2 4 9 23 65 197 626 2056 6918 23714 82500 290512 1033412 3707852 */

int nums(long n) {
        int i = 0;
        while (n >= dlt[i])
                i++;
        return i;
}

long min_by(int n) { return dlt[n - 1]; }

void print_tree(long n) {
        if (n == 1) {
                printf("X");
                return;
        }
        if (n == 2) {
                printf("X(X)");
                return;
        }

        int i = 0;
        int nx, ny;
        long d;
        long x, y;
        while (n >= dlt[i])
                i++;

        i--;

        d = n - dlt[i];
        x = 0;
        y = dlt[i - 1];
        ny = i;
        nx = 0;
        while (d > 0) {
                y++;
                ny = nums(y);
                if (ny + nx != i) {
                        x += 1;
                        nx = nums(x);
                        y = min_by(i - nx);
                        y--;
                } else {
                        d--;
                }
        }

        if (x > 0) {
                printf("(");
                print_tree(x);
                printf(")");
        }
        printf("X");
        if (y > 0) {
                printf("(");
                print_tree(y);
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
