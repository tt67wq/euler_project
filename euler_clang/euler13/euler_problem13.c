/*
 * =====================================================================================
 *
 *       Filename:  euler_problem13.c
 *
 *    Description:  欧拉计划13题
 *
 *        Version:  1.0
 *        Created:  2018-07-19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 60

int main() {
        char n1[MAX_LEN] = "37107287533902102798797998220837590246510135740250";
        char n2[MAX_LEN] = "46376937677490009712648124896970078050417018260538";

        int an1[MAX_LEN];
        int an2[MAX_LEN];
        memset(an1, 0, sizeof(an1));
        memset(an2, 0, sizeof(an2));

        int nl1 = strlen(n1);
        int nl2 = strlen(n2);

        int i, j;

        j = 0;
        for (i = nl1 - 1; i >= 0; i--)
                an1[j++] = n1[i] - '0';

        j = 0;
        for (i = nl2 - 1; i >= 0; i--)
                an2[j++] = n2[i] - '0';

        for (i = 0; i < MAX_LEN; i++) {
                an1[i] += an2[i];
                if (an1[i] >= 10) {
                        an1[i] -= 10;
                        an1[i + 1]++;
                }
        }

        int bstartOutput = 0;

        for (i = MAX_LEN; i >= 0; i--) {
                if (bstartOutput > 0)
                        printf("%d", an1[i]);
                else if (an1[i]) {
                        printf("%d", an1[i]);
                        bstartOutput = 1;
                }
        }
        if (bstartOutput == 0)
                printf("0");
        return 0;
}
