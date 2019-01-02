/*
 * =====================================================================================
 *
 *       Filename:  euler166.c
 *
 *    Description:  欧拉计划166题
 *
 *        Version:  1.0
 *        Created:  2018-12-29
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

#define M 9
int results[16] = {0}; //保存已经找到的结果前缀数组
int SUM = 0;

int min(int a, int b) {
        if (a < b)
                return a;
        return b;
}

void bfs(int s, int deep) {
        if (deep == 15) {
                for (int i = 0; i < 4; i++) {
                        printf("%d", results[i]);
                }
                printf(" ");
                for (int i = 4; i < 8; i++) {
                        printf("%d", results[i]);
                }
                printf(" ");
                for (int i = 8; i < 12; i++) {
                        printf("%d", results[i]);
                }
                printf(" ");
                for (int i = 12; i < 16; i++) {
                        printf("%d", results[i]);
                }
                SUM++;
                printf(" sum => %d\n", SUM);
                return;
        }
        if (deep < 3) {
                for (int i = 0; i <= M; i++) {
                        results[deep] = i;
                        bfs(s, deep + 1);
                }
        }
        if (deep == 3) {
                for (int i = 0; i <= M; i++) {
                        results[deep] = i;
                        s = results[0] + results[1] + results[2] + results[3];
                        bfs(s, deep + 1);
                }
        }
        if (deep == 4) {
                for (int i = 0; i <= min(s, M); i++) {
                        results[deep] = i;
                        bfs(s, deep + 1);
                }
        }

        if (deep == 5) {
                for (int i = 0; i <= min(s - results[4], M); i++) {
                        results[deep] = i;
                        bfs(s, deep + 1);
                }
        }

        if (deep == 6) {
                for (int i = 0; i <= min(s - results[4] - results[5], M); i++) {
                        int t7 = s - results[4] - results[5] - i;
                        if (t7 >= 0 && t7 <= M) {
                                results[6] = i;
                                results[7] = t7;
                                bfs(s, deep + 2);
                        }
                }
        }
        if (deep == 8) {
                for (int i = 0; i <= min(s - results[0] - results[4], M); i++) {
                        int t12 = s - results[0] - results[4] - i;
                        if (t12 >= 0 && t12 <= M) {
                                int t9 = s - results[3] - results[6] - t12;
                                if (t9 >= 0 && t9 <= M) {
                                        int t13 = s - results[1] - results[5] - t9;
                                        if (t13 >= 0 && t13 <= M) {
                                                int dt10 = s - results[0] - results[5] - i - t9 + results[3] + results[7];
                                                if (dt10 >= 0 && dt10 <= 18 && dt10 % 2 == 0) {
                                                        int t10 = dt10 / 2;
                                                        int t14 = s - results[2] - results[6] - t10;
                                                        if (t14 >= 0 && t14 <= M) {
                                                                int t11 = s - i - t9 - t10;
                                                                if (t11 >= 0 && t11 <= M) {
                                                                        int t15 = s - results[0] - results[5] - t10;
                                                                        if (t15 >= 0 && t15 <= M) {
                                                                                if (t12 + t13 + t14 + t15 == s) {
                                                                                        results[8] = i;
                                                                                        results[9] = t9;
                                                                                        results[10] = t10;
                                                                                        results[11] = t11;
                                                                                        results[12] = t12;
                                                                                        results[13] = t13;
                                                                                        results[14] = t14;
                                                                                        results[15] = t15;
                                                                                        bfs(s, 15);
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}

int main() {
        clock_t begin = clock();
        bfs(0, 0);
        clock_t end = clock();
	double timespent = end - begin;
        printf("time use => %lfs\n", (double)(timespent / CLOCKS_PER_SEC));
        return 0;
}
