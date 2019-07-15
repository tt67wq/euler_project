/*
 * =====================================================================================
 *
 *       Filename:  jugs.c
 *
 *    Description:  zoj 1005
 *
 *        Version:  1.0
 *        Created:  2019-07-15
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

int CA;
int CB;
int N;

void solve(int a, int b) {

        while (1) {
                if (a == 0) {
                        a = CA;
                        printf("fill A\n");
                }
                if (a + b > CB) {
                        a = a + b - CB;
                        b = CB;
                        printf("pour A B\n");
                } else {
                        b = a + b;
                        a = 0;
                        printf("pour A B\n");
                }
                if (b == N) {
                        printf("success\n");
                        break;
                }
                if (b == CB) {
                        b = 0;
                        printf("empty B\n");
                }
        }
}

int main() {

        while (scanf("%d %d %d", &CA, &CB, &N) != EOF) {
                solve(0, 0);
        }
        return 0;
}
