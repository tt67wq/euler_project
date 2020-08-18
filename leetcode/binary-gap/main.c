/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-18
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG

void reverse(int *A, int Size) {
        int i, tmp;
        for (i = 0; i < Size / 2; i++) {
                tmp = A[i];
                A[i] = A[Size - 1 - i];
                A[Size - 1 - i] = tmp;
        }
}

int binaryGap(int N) {
        int bits[32] = {0};
        int *bitsPtr = bits;
        int res = 0, idx = 0;
        while (N) {
                (*bitsPtr) = N % 2;
                bitsPtr++;
                N /= 2;
                idx++;
        }

        reverse(bits, idx);
        int p0 = 0, p1 = 0;
        for (int i = 0; i < idx; i++) {
                if (bits[i] == 1) {
                        p1 = i;
                        res = res > p1 - p0 ? res : p1 - p0;
                        p0 = p1;
                }
        }

        return res;
}

int main() {
        int n;
        while (1) {
                scanf("%d", &n);
                int ans = binaryGap(n);
                printf("%d\n", ans);
        }

        return 0;
}