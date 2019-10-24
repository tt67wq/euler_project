/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-10-24
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

void string_slice(char *s, char *des, int start, int end) {
        int i, j = 0;
        for (i = start; i < end; i++)
                des[j++] = s[i];
}

char *minWindow(char *s, char *t) {
        int sl, tl, l, r, i;
        int sf[64] = {0};
        int tf[64] = {0};
        int edge[2];
        char *res;

        sl = strlen(s);
        tl = strlen(t);

        for (i = 0; i < tl; i++)
                tf[t[i] - 'A']++;

        l = 0;
        r = -1;
        edge[0] = -1;
        edge[1] = sl + 1;

        while (l <= sl - tl) {
                /* win < tl */
                if (r - l + 1 < tl) {
                        if (r + 1 < sl) {
                                sf[s[++r] - 'A']++;
                                continue;
                        } else {
                                break;
                        }
                }
                /* win >= tl */
                i = 0;
                while (i < 64) {
                        if (sf[i] < tf[i])
                                break;
                        i++;
                }

                if (i < 64) {
                        // not cover
                        if (r + 1 < sl)
                                sf[s[++r] - 'A']++;
                        else
                                break;
                } else {
                        // cover
                        if (r - l + 1 == tl) { // match
                                res = (char *)calloc(tl + 1, sizeof(char));
                                string_slice(s, res, l, r + 1);
                                return res;
                        } else {
                                // wider
                                if (r - l < edge[1] - edge[0]) {
                                        edge[0] = l;
                                        edge[1] = r;
                                }
                                sf[s[l++] - 'A']--;
                        }
                }
        }

        if (edge[0] == -1)
                return "";

        res = (char *)calloc(edge[1] - edge[0] + 2, sizeof(char));
        string_slice(s, res, edge[0], edge[1] + 1);
        return res;
}

int main() {
        char s[] = "ADOBECODEBANC";
        char t[] = "BAN";
        printf("%s\n", minWindow(s, t));
        return 0;
}
