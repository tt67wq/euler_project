/*
 * =====================================================================================
 *
 *       Filename:  euler47.c
 *
 *    Description:  欧拉计划47题
 *
 *        Version:  1.0
 *        Created:  2018-11-06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fac_nums(int n, int (*facs)[2]) {
        int i, j;
        int index = 0;
        for (i = 2; i <= n; i++) {
                if (n % i == 0) {
                        n /= i;
                        int exists = 0;
                        for (j = 0; j < index; j++) {
                                if (facs[j][0] == i) {
                                        facs[j][1]++;
                                        exists = 1;
                                        break;
                                }
                        }
                        if (!exists) {
                                facs[index][0] = i;
                                facs[index][1] = 1;
                                index++;
                                if (index > 4)
                                        return 0;
                        }
                        i--;
                }
        }
        return index;
}

int main() {

	clock_t begin = clock();
        int index = 2;
        int res = 0;

        while (1) {
                /* printf("%d\n", index); */
                int facs1[4][2] = {{0}};
                int facs2[4][2] = {{0}};
                int facs3[4][2] = {{0}};
                int facs4[4][2] = {{0}};
                if (fac_nums(index, facs1) == 4 && fac_nums(index + 1, facs2) == 4 &&
                    fac_nums(index + 2, facs3) == 4 && fac_nums(index + 3, facs4) == 4) {
                        // 比较独立性
                        int diff = 1;

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs1[i][0] == facs2[j][0] &&
                                            facs1[i][1] == facs2[j][1])
                                                diff = 0;
                                }
                        }
                        if (!diff) {
                                index++;
                                continue;
                        }

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs1[i][0] == facs3[j][0] &&
                                            facs1[i][1] == facs3[j][1])
                                                diff = 0;
                                }
                        }

                        if (!diff) {
                                index++;
                                continue;
                        }

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs1[i][0] == facs4[j][0] &&
                                            facs1[i][1] == facs4[j][1])
                                                diff = 0;
                                }
                        }
                        if (!diff) {
                                index++;
                                continue;
                        }

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs2[i][0] == facs3[j][0] &&
                                            facs2[i][1] == facs3[j][1])
                                                diff = 0;
                                }
                        }
                        if (!diff) {
                                index++;
                                continue;
                        }

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs2[i][0] == facs4[j][0] &&
                                            facs2[i][1] == facs4[j][1])
                                                diff = 0;
                                }
                        }
                        if (!diff) {
                                index++;
                                continue;
                        }

                        for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                        if (facs4[i][0] == facs3[j][0] &&
                                            facs4[i][1] == facs3[j][1])
                                                diff = 0;
                                }
                        }
                        if (!diff) {
                                index++;
                                continue;
                        }

                        if (diff) {
                                res = index;
                                break;
                        }
                }
                index++;
        }
        clock_t end = clock();
        double timespent = end - begin;
        printf("result => %d time use => %lfs\n", res, (double)(timespent / CLOCKS_PER_SEC));


        return 0;
}
