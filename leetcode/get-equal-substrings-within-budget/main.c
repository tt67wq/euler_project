/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-05
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

#define ABS(n) ((n) > 0 ? (n) : 0 - (n))

int equalSubstring(char *s, char *t, int maxCost) {
        int l, i, ans, *diff, head, rear;

        ans = 0;
        l = strlen(s);
        diff = malloc(sizeof(int) * (l + 1)); // diff[i] = sum(abs(t[i]-s[i])) for i in [0, i)

        diff[0] = 0;
        for (i = 1; i <= l; i++) {
                diff[i] = diff[i - 1] + ABS(t[i - 1] - s[i - 1]);
                // printf("%d ", diff[i]);
        }
        // puts("");

        head = 0, rear = 0;

        while (head <= l) {
                if (head >= rear && diff[head] - diff[rear] <= maxCost) {
                        if (head - rear > ans) {
                                ans = head - rear;
                        }
                } else {
                        rear++;
                        continue;
                }

                head++;
        }

        free(diff);
        return ans;
}

int main() {
        printf("%d\n", equalSubstring("abcd", "bcdf", 3));
        printf("%d\n", equalSubstring("abcd", "cdef", 3));
        printf("%d\n", equalSubstring("abcd", "acde", 0));
        printf("%d\n", equalSubstring("krpgjbjjznpzdfy", "nxargkbydxmsgby", 14));
        return 0;
}