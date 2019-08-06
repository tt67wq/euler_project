/*
 * =====================================================================================
 *
 *       Filename:  system_overload.c
 *
 *    Description:  zoj 1088
 *
 *        Version:  1.0
 *        Created:  2019-08-06
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

int n;

int solve() {
        char *vs;
        int i, j, k;
        int m;
        vs = (char *)malloc(n * sizeof(char));
        for (m = 2;; m++) {
                memset(vs, 0, n * sizeof(char));
                i = n - 1;
                j = 0;
                k = 0;
                vs[j] = 1;
                while (i) {
                        j++;
                        if (j >= n)
                                j %= n;
                        if (!vs[j])
                                k++;
                        if (k == m) {
                                if (j == 1)
                                        break;
                                vs[j] = 1;
                                i--;
                                k = 0;
                        }
                }
                if (i == 1) {
                        free(vs);
                        return m;
                }
        }

        return 0;
}

int main() {
        while (scanf("%d", &n) != EOF) {
                if (!n)
                        break;
                printf("%d\n", solve());
        }
        return 0;
}
