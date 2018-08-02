/*
 * =====================================================================================
 *
 *       Filename:  euler_problem18.c
 *
 *    Description:  欧拉计划18题
 *
 *        Version:  1.0
 *        Created:  2018-08-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wanqiang
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 14

int sum(int x, int y, int sofar, int *t) {
        int n = t[x + (y * (y + 1) >> 1)];

        if (y < HEIGHT) {
                int right = sum(x + 1, y + 1, sofar + n, t);
                int left = sum(x, y + 1, sofar + n, t);
                return right > left ? right : left;
        }

        return sofar + n;
}

int main() {
        FILE *fp;
        char ch;
        int tr[120] = {0};

        if ((fp = fopen("data.txt", "rt")) == NULL) {
                exit(1);
        }
        ch = fgetc(fp);
        int i = 0;
        int tmp;
        while (ch != EOF) {
                if (ch == '\n') {
                        tr[i++] = tmp;
                        tmp = 0;
                        ch = fgetc(fp);
                        continue;
                }
                if (ch == ' ') {
                        ch = fgetc(fp);
                        tr[i++] = tmp;
                        tmp = 0;
                        continue;
                }
                tmp = tmp * 10 + ch - '0';
                ch = fgetc(fp);
        }

        fclose(fp);

        int res = sum(0, 0, 0, tr);
        printf("%d\n", res);
        return 0;
}
