/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-19
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minKBitFlips(int *A, int ASize, int K) {
        int *diff, ans, revCnt;
        size_t _size;

        _size = sizeof(int) * (ASize + 1);
        diff = malloc(_size);
        memset(diff, 0, _size);
        ans = 0, revCnt = 0;

        for (int i = 0; i < ASize; i++) {
                revCnt += diff[i];
                if ((A[i] + revCnt) % 2 == 0) {
                        if (i + K > ASize) {
                                return -1;
                        }
                        ++ans;
                        ++revCnt;
                        --diff[i + K];
                }
        }

        free(diff);
        return ans;
}

int main() {
        int A[] = {0, 0, 0, 1, 0, 1, 1, 0};
        int ans = minKBitFlips(A, 8, 3);
        printf("%d\n", ans);
        return 0;
}