/*
 * =====================================================================================
 *
 *       Filename:  euler213.c
 *
 *    Description:  欧拉计划213题
 *
 *        Version:  1.0
 *        Created:  2019-06-25
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
#include <time.h>

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

void jumps(double *state) {

        int index = 50;
        while (index) {
                double buffer[900] = {0.0};

                for (int i = 0; i < 900; i++) {
                        if (state[i] > 0.0) {
                                double base = state[i];
                                if (is_corner(i)) {
                                        double tmp = base * 0.5;
                                        if (i == 0) {
                                                buffer[1] += tmp;
                                                buffer[30] += tmp;
                                        } else if (i == 29) {
                                                buffer[28] += tmp;
                                                buffer[59] += tmp;
                                        } else if (i == 870) {
                                                buffer[871] += tmp;
                                                buffer[840] += tmp;
                                        } else {
                                                buffer[869] += tmp;
                                                buffer[898] += tmp;
                                        }
                                } else if (is_board(i)) {
                                        double tmp = base * 1.0 / 3;
                                        if (i < 30) {
                                                buffer[i + 1] += tmp;
                                                buffer[i - 1] += tmp;
                                                buffer[i + 30] += tmp;
                                        } else if (i % 30 == 0) {
                                                buffer[i - 30] += tmp;
                                                buffer[i + 30] += tmp;
                                                buffer[i + 1] += tmp;
                                        } else if (i % 30 == 29) {
                                                buffer[i - 30] += tmp;
                                                buffer[i + 30] += tmp;
                                                buffer[i - 1] += tmp;
                                        } else {
                                                buffer[i + 1] += tmp;
                                                buffer[i - 1] += tmp;
                                                buffer[i - 30] += tmp;
                                        }
                                } else {
                                        double tmp = base * 0.25;
                                        buffer[i + 1] += tmp;
                                        buffer[i - 1] += tmp;
                                        buffer[i + 30] += tmp;
                                        buffer[i - 30] += tmp;
                                }
                        }
                }
                index--;
                memcpy(state, buffer, sizeof(double) * 900);
        }
        return;
}

int main(int argc, const char *argv[]) {
        double res[900] = {0};
        double expectation = 0.0;

        // init
        for (int j = 0; j < 900; j++) {
                res[j] = 1.0;
        }

        for (int i = 0; i < 900; i++) {
                double state[900] = {0.0};
                state[i] = 1.0;
                jumps(state);

                for (int j = 0; j < 900; j++) {
                        res[j] *= (1.0 - state[j]);
                }
        }
        for (int i = 0; i < 900; i++) {
                expectation += res[i];
        }
        printf("%0.7f\n", expectation);
        printf("330.721154\n");

        return 0;
}
