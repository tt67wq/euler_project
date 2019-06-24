/*
 * =====================================================================================
 *
 *       Filename:  euler213.c
 *
 *    Description:  欧拉计划213题
 *
 *        Version:  1.0
 *        Created:  2019-06-24
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
#define N 100000

int fleas[900];
int grid[900];

int is_corner(int pos) {
        int res = 0;
        switch (pos) {
        case 0:
                res = 1;
                break;
        case 29:
                res = 1;
                break;
        case 870:
                res = 1;
                break;
        case 899:
                res = 1;
                break;
        default:
                res = 0;
                break;
        }
        return res;
}
int is_board(int pos) {
        if (pos < 30)
                return 1;
        if (pos % 30 == 0)
                return 1;
        if (pos % 30 == 29)
                return 1;
        if (pos > 870)
                return 1;
        return 0;
}

void jump_once() {

        for (int i = 0; i < 900; i++) {
                int d = 0;
                if (is_corner(fleas[i])) {
                        // 角落
                        d = (int)(2.0 * rand() / (RAND_MAX + 1.0));
                        if (fleas[i] == 0) {
                                switch (d) {
                                case 0:
                                        fleas[i] = 1;
                                        break;
                                default:
                                        fleas[i] = 30;
                                        break;
                                }
                        } else if (fleas[i] == 29) {
                                switch (d) {
                                case 0:
                                        fleas[i] = 28;
                                        break;
                                default:
                                        fleas[i] = 59;
                                        break;
                                }
                        } else if (fleas[i] == 870) {
                                switch (d) {
                                case 0:
                                        fleas[i] = 840;
                                        break;
                                default:
                                        fleas[i] = 871;
                                        break;
                                }
                        } else {
                                switch (d) {
                                case 0:
                                        fleas[i] = 869;
                                        break;
                                default:
                                        fleas[i] = 898;
                                        break;
                                }
                        }
                } else if (is_board(fleas[i])) {
                        d = (int)(3.0 * rand() / (RAND_MAX + 1.0));
                        if (fleas[i] < 30) {
                                switch (d) {
                                case 0:
                                        fleas[i] += 1;
                                        break;
                                case 1:
                                        fleas[i] += 30;
                                        break;
                                default:
                                        fleas[i] -= 1;
                                        break;
                                }
                        } else if (fleas[i] % 30 == 0) {
                                switch (d) {
                                case 0:
                                        fleas[i] -= 30;
                                        break;
                                case 1:
                                        fleas[i] += 1;
                                        break;
                                default:
                                        fleas[i] += 30;
                                        break;
                                }
                        } else if (fleas[i] % 30 == 29) {
                                switch (d) {
                                case 0:
                                        fleas[i] -= 30;
                                        break;
                                case 1:
                                        fleas[i] -= 1;
                                        break;
                                default:
                                        fleas[i] += 30;
                                        break;
                                }
                        } else {
                                switch (d) {
                                case 0:
                                        fleas[i] -= 1;
                                        break;
                                case 1:
                                        fleas[i] -= 30;
                                        break;
                                default:
                                        fleas[i] += 1;
                                        break;
                                }
                        }
                } else {
                        d = (int)(4.0 * rand() / (RAND_MAX + 1.0));
                        switch (d) {
                        case 0:
                                fleas[i] -= 30;
                                break;
                        case 1:
                                fleas[i] += 1;
                                break;
                        case 2:
                                fleas[i] += 30;
                                break;
                        case 3:
                                fleas[i] -= 1;
                                break;
                        }
                }
        }
        return;
}

int expectation() {
        int counter = 0;
        // init
        int grid[900] = {0};
        for (int i = 0; i < 900; i++)
                fleas[i] = i;

        // jump 50 times;
        for (int i = 0; i < 3; i++)
                jump_once();

        for (int j = 0; j < 900; j++) {
                /* printf("fleas[%d] = %d\n", j, fleas[j]); */
                grid[fleas[j]] += 1;
        }

        for (int j = 0; j < 900; j++) {
                if (grid[j] == 0)
                        counter++;
        }

        return counter;
}

int main(int argc, const char *argv[]) {
        srand((int)time(0));

        int total = 0;
        for (int i = 0; i < N; i++) {
                total += expectation();
        }
        printf("%0.6f\n", (float)total / N);
        printf("330.721154\n");

        return 1;
}
