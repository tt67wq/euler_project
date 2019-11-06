/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-06
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int maxTurbulenceSize(int *A, int ASize) {
        int i, pre_len, ans;
        char pre = '=';

        pre_len = 1;
        ans = 1;

        for (i = 1; i < ASize; i++) {
                if (A[i] == A[i - 1]) {
                        pre_len = 1;
                        pre = '=';
                } else if (A[i] > A[i - 1] && pre == '<' || A[i] < A[i - 1] && pre == '>') {
                        pre_len += 1;
                } else {
                        pre_len = 2;
                }
                pre = A[i] > A[i - 1] ? '>' : '<';
                ans = pre_len > ans ? pre_len : ans;
        }
        return ans;
}

int main() { return 0; }
