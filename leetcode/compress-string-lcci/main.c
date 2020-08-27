/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2020-08-27
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

#define DEBUG

char *compressString(char *S) {
        if (strlen(S) < 3) {
                return S;
        }
        char a = S[0];
        int c = 0;
        char *ans = (char *)calloc(sizeof(char), 2 * strlen(S));
        char *pt = ans;
        int buff[10] = {0};
        for (int i = 0; i < strlen(S); i++) {
                if (S[i] == a) {
                        c++;
                } else {
                        (*pt) = a;
                        pt++;

                        int j = 0;
                        while (c) {
                                buff[j++] = c % 10;
                                c /= 10;
                        }
                        while (j) {
                                (*pt) = buff[--j] + '0';
                                pt++;
                        }

                        a = S[i];
                        c = 1;
                }
        }
        (*pt) = a;
        pt++;

        int j = 0;
        while (c) {
                buff[j++] = c % 10;
                c /= 10;
        }
        while (j) {
                (*pt) = buff[--j] + '0';
                pt++;
        }

        (*pt) = '\0';

        if (strlen(S) <= strlen(ans)) {
                return S;
        }
        return ans;
}

int main() {
        char *ans = compressString("rrrrrLLLLLPPPPPPRRRRRgggNNNNNVVVVVVVVVVDDDDDDDDDDIIIIIIIIIIllll"
                                   "lllAAAAqqqqqqqbbbNNNNffffff");
        printf("%s\n", ans);
        return 0;
}