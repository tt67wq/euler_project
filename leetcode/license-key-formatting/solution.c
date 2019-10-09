/*
 * =====================================================================================
 *
 *       Filename:  solution.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-09
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

void reverse_string(char *str) {
        /* skip null */
        if (str == 0) {
                return;
        }

        /* skip empty string */
        if (*str == 0) {
                return;
        }

        /* get range */
        char *start = str;
        char *end = start + strlen(str) - 1; /* -1 for \0 */
        char temp;

        /* reverse */
        while (end > start) {
                /* swap */
                temp = *start;
                *start = *end;
                *end = temp;

                /* move */
                ++start;
                --end;
        }
}

char *licenseKeyFormatting(char *S, int K) {
        char *R = (char *)calloc(100000, sizeof(char));

        int i, j, k, first;

        reverse_string(S);

        j = 0;
        k = 0;
        first = 1;
        for (i = 0;; i++) {
                if (S[i] == '\0')
                        break;
                if (S[i] == '-')
                        continue;
                if (k == 0) {
                        if (first == 1)
                                first = 0;
                        else {
                                R[j] = '-';
                                j += 1;
                        }
                }

                if (S[i] >= 'a' && S[i] <= 'z')
                        R[j] = S[i] - 32;
                else
                        R[j] = S[i];
                k += 1;
                if (k == K)
                        k = 0;

                j += 1;
        }
        reverse_string(R);
        return R;
}

int main() {
        char s[] = "2-4A0r7-4k";
        char *r = licenseKeyFormatting(s, 4);
        printf("%s\n", r);
        /* printf("%lu\n", strlen(s)); */
        return 0;
}
