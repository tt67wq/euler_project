/*
 * =====================================================================================
 *
 *       Filename:  calandar.c
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

typedef struct _date {
        long year;
        int month;
        int day;
} date;

char *ds[5] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

int diff(date *d1, date *d2) {
        int n1, n2;
        int res;
        n1 = d2->day - d1->day;
        if (n1 < 0) {
                n1 += 30;
                (d2->month)--;
        }
        n2 = d2->month - d1->month;
        if (n2 < 0) {
                n2 += 12;
                (d2->year)--;
        }
        res = (int)(((long)(d2->year - d1->year) * 360 + n2 * 30 + n1) % 5);
        if (res < 0)
                res += 5;
        return res;
}

int main() {
        int n, i;
        date d1, d2;
        char day[10];
        scanf("%d", &n);
        while (n > 0) {
                scanf("%ld %d %d %s", &d1.year, &d1.month, &d1.day, day);
                scanf("%ld %d %d", &d2.year, &d2.month, &d2.day);
                for (i = 0; i < 5; i++) {
                        if (strcmp(day, ds[i]) == 0)
                                break;
                }
                printf("%s\n", ds[(i+diff(&d1, &d2))%5]);
                n--;
        }
        return 0;
}
