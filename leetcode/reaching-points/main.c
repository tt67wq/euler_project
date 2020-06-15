/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-06-15
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

#define DEBUG
bool dfs(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) {
                return true;
        } else if (sx == tx && sy < ty) {
                if ((ty - sy) % tx == 0) {
                        return true;
                } else {
                        return false;
                }
        } else if (sx < tx && sy == ty) {
                if ((tx - sx) % ty == 0) {
                        return true;
                } else {
                        return false;
                }
        }

        if (tx > ty) {
                if (dfs(sx, sy, tx - ty, ty)) {
                        return true;
                }
        } else if (tx < ty) {
                if (dfs(sx, sy, tx, ty - tx)) {
                        return true;
                }
        }

        return false;
}

bool reachingPoints(int sx, int sy, int tx, int ty) { return dfs(sx, sy, tx, ty); }

int main() {

        printf("%d\n", reachingPoints(44, 43, 921197891, 702724365));
        return 0;
}
