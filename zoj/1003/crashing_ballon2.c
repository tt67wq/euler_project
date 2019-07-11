/*
 * =====================================================================================
 *
 *       Filename:  crashing_ballon2.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-07-11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int pa, pb, winner;

void challenge(int a, int b, int n) {
        if (winner == pa)
                return;
        if (b == 1) {
                if (a == 1)
                        winner = pa;
                else
                        winner = pb;
        }
        if (n <= 100) {
                if (a % n == 0)
                        challenge(a / n, b, n + 1);
                if (b % n == 0)
                        challenge(a, b / n, n + 1);
                challenge(a, b, n + 1);
        }
}

void solve() {
        if (pa == pb) {
                printf("%d\n", pa);
                return;
        }
        if (pa < pb) {
                int tmp = pb;
                pb = pa;
                pa = tmp;
        }

        winner = 0;
        challenge(pa, pb, 2);
        if (winner == 0)
                winner = pa;
        printf("%d\n", winner);
}

int main() {
        /* FILE *fp; */
        /* fp = fopen("test.txt", "r"); */

        /* while (fscanf(fp, "%d %d", &pa, &pb) != EOF) { */
        while (scanf("%d %d", &pa, &pb) != EOF) {
                /* printf("%d %d\n", pa, pb); */
                solve();
        }
        return 0;
}
