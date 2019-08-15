/*
 * =====================================================================================
 *
 *       Filename:  hangover.c
 *
 *    Description:  zoj 1045
 *
 *        Version:  1.0
 *        Created:  2019-08-15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

double ls[MAX + 1];

void bin_search(double len, int *cards) {
        int mid, head = 0, tail = MAX - 1;
        while (head < tail - 1) {
                mid = (head + tail) / 2;

                if (len > ls[mid]) {
                        head = mid;
                } else {
                        tail = mid;
                }
        }
        *cards = head + 1;
}

void init() {
        int i, j = 0;
        double acc = 0.0;
        for (i = 2; i < MAX + 2; i++) {
                acc += (double)1 / i;
                ls[++j] = acc;
        }
}

int main() {
        init();
        double l;
        int cards;
        while (1) {
                scanf("%lf", &l);
                if (l == 0.00)
                        break;
                bin_search(l, &cards);
                printf("%d card(s)\n", cards);
        }

        return 0;
}
