/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-31
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

int repeatedStringMatch(char *A, char *B) {
        int i, j, k, count, la, lb;

        la = strlen(A);
        lb = strlen(B);
        i = 0;

        for (i = 0; i < la; i++) {
                if (A[i] == B[0]) {
                        k = i;
                        count = 1;
                        j = 0;
                        while (A[k] == B[j]) {
                                k++;
                                j++;
                                if (j >= lb)
                                        return count;
                                if (k >= la) {
                                        k = 0;
                                        count++;
                                }
                        }
                }
        }
        return -1;
}

int main() {
        char A[] = "abcd";
        char B[] = "cdabcdab";
        printf("%d\n", repeatedStringMatch(A, B));
        return 0;
}
