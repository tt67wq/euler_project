/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-12-17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decodeAtIndex(char *S, int K) {
        int i, l;
        char *ans;
        unsigned long long size;

        l = strlen(S);
        size = 0;
        ans = (char *)calloc(2, sizeof(char));

        for (i = 0; i < l; i++) {
                if (S[i] >= '0' && S[i] <= '9') {
                        size *= (S[i] - '0');
                } else {
                        size++;
                }
        }
        for (i = l - 1; i >= 0; i--) {
                K %= size;
                if (K == 0 && (S[i] >= 'a' && S[i] <= 'z')) {
                        ans[0] = S[i];
                        break;
                }
                if (S[i] > '0' && S[i] <= '9') {
                        size /= (S[i] - '0');
                } else {
                        size--;
                }
        }
        ans[1] = '\0';
        return ans;
}

int main() {
        char S[] = "a2b3c4d5e6f7g8h9";
        // aabbbccccddddd...
        printf("%s\n", decodeAtIndex(S, 10));
        return 0;
}
