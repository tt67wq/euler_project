/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-29
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

#define Q 0
#define W 1
#define E 2
#define R 3

int word2num(char a) {
        int n;
        switch (a) {
        case 'Q':
                n = Q;
                break;
        case 'W':
                n = W;
                break;
        case 'E':
                n = E;
                break;
        case 'R':
                n = R;
                break;
        }
        return n;
}

int balancedString(char *s) {

        int vis[4] = {0};
        int i, l, left, right, ans, avg;

        l = strlen(s);
        avg = l / 4;
        ans = l;

        for (i = 0; i < l; i++)
                vis[word2num(s[i])]++;

        left = 0;
        right = 0;
        while (right < l) {
                vis[word2num(s[right])]--;
                while (left < l && vis[Q] <= avg && vis[W] <= avg && vis[E] <= avg && vis[R] <= avg) {
                        ans = ans < right - left + 1 ? ans : right - left + 1;
                        vis[word2num(s[left])]++;
                        left++;
                }
                right++;
        }
        return ans;
}

int main() {
        printf("%d\n", balancedString("QWRR"));
        return 0;
}
