/*
 * =====================================================================================
 *
 *       Filename:  stones.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-09-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

long a[MAX];

int main() {
        int c, i, n;
        long sum, avg, steps;
        scanf("%d", &c);
        while (c > 0) {
                sum = 0;
                steps = 0;
                bzero(a, sizeof(long) * MAX);

                scanf("%d", &n);

                for (i = 0; i < n; i++) {
                        scanf("%ld", &a[i]);
                        sum += a[i];
                }
                avg = sum / n;
                for (i = 0; i < n; i++) {
                        if (a[i] <= avg)
                                continue;
                        steps += (a[i] - avg);
                }
                printf("%ld\n", steps);
                c--;
        }
        return 0;
}
