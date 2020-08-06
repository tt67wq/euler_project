/*
 * =====================================================================================
 *
 *       Filename:  robot.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
#define min(a, b) ((a) < (b) ? (a) : (b))

bool inList(long *set, int setSize, long pos) {
        for (int i = 0; i < setSize; i++) {
                if (set[i] == pos) {
                        return true;
                }
        }
        return false;
}

bool robot(char *command, int **obstacles, int obstaclesSize, int *obstaclesColSize, int x, int y) {
        int xx = 0, yy = 0;
        int l = strlen(command);
        long *posSet = (long *)malloc(sizeof(long) * (l + 1));

        long *sp = posSet;
        *sp = 0;
        sp++;

        for (int i = 0; i < l; i++) {
                if (command[i] == 'U') {
                        yy++;
                } else {
                        xx++;
                }
                *sp = (((long)xx) << 30) | yy;
                // printf("%ld\n", *sp);
                sp++;
        }

        int circle = min(x / xx, y / yy);
        long originPos = ((long)(x - circle * xx) << 30) | (y - circle * yy);
        // printf("%ld\n", originPos);
        if (!inList(posSet, l + 1, originPos)) {
                // printf("target not in road\n");
                free(posSet);
                return false;
        }

        for (int i = 0; i < obstaclesSize; i++) {
                int ox = obstacles[i][0], oy = obstacles[i][1];
                if (ox > x || oy > y)
                        continue;
                int oc = min(ox / xx, oy / yy);
                long op = ((long)(ox - oc * xx) << 30) | (oy - oc * yy);
                if (inList(posSet, l + 1, op)) {
                        // printf("{%d, %d}, %ld in road\n", ox, oy, op);
                        free(posSet);
                        return false;
                }
        }

        free(posSet);
        return true;
}

int main() {
        // "UURRUUU"
        // [[4, 5], [6, 1], [7, 10], [9, 1], [1, 1], [5, 0], [2, 8]]
        // 946
        // 2365
        char *command = "UURRUUU";
        int ob0[] = {4, 5}, ob1[] = {6, 1}, ob2[] = {7, 10}, ob3[] = {9, 1}, ob4[] = {1, 1},
            ob5[] = {5, 0}, ob6[] = {2, 8};
        int **obstacles = (int **)malloc(sizeof(int **) * 7);
        obstacles[0] = ob0;
        obstacles[1] = ob1;
        obstacles[2] = ob2;
        obstacles[3] = ob3;
        obstacles[4] = ob4;
        obstacles[5] = ob5;
        obstacles[6] = ob6;
        bool res = robot(command, obstacles, 7, NULL, 946, 2365);
        free(obstacles);
        printf("%d\n", res);
        return 0;
}