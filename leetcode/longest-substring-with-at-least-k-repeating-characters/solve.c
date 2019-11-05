/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2019-11-05
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

int process(char *s, int k, int l, int h) {
        if (h - l + 1 < k)
                return 0;

        int i, t1, t2;
        int vis[26] = {0};

        /* 字母计数 */
        for (i = l; i <= h; i++)
                vis[s[i] - 'a']++;

        /* 裁剪两端的计数不够的字母 */
        while (h - l + 1 >= k && vis[s[l] - 'a'] < k)
                l++;

        while (h - l + 1 >= k && vis[s[h] - 'a'] < k)
                h--;

        /* 如果有计数不够的字母夹在中间，分割开之后处理 */
        for (i = l; i <= h; i++) {
                if (vis[s[i] - 'a'] < k) {
                        t1 = process(s, k, l, i - 1);
                        t2 = process(s, k, i + 1, h);
                        return t1 > t2 ? t1 : t2;
                }
        }
        return h - l + 1;
}
int longestSubstring(char *s, int k) {
        int len;
        len = strlen(s);
        if (k < 2)
                return len;

        return process(s, k, 0, len - 1);
}

int main() {
        char s[] = "aaabb";
        int k = 3;
        printf("%d\n", longestSubstring(s, k));
        return 0;
}
