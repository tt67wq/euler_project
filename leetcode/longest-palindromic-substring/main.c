/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-02-25
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

// 给你一个字符串 s，找到 s 中最长的回文子串。

//  

// 示例 1：

// 输入：s = "babad"
// 输出："bab"
// 解释："aba" 同样是符合题意的答案。
// 示例 2：

// 输入：s = "cbbd"
// 输出："bb"
// 示例 3：

// 输入：s = "a"
// 输出："a"
// 示例 4：

// 输入：s = "ac"
// 输出："a"
//  

// 提示：

// 1 <= s.length <= 1000
// s 仅由数字和英文字母（大写和/或小写）组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/longest-palindromic-substring
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int expendAroundCenter(char *s, int left, int right) {
        int l = left, r = right, s_len = strlen(s);
        while (l >= 0 && r < s_len && s[l] == s[r]) {
                l--;
                r++;
        }
        return r - l - 1;
}

char *longestPalindrome(char *s) {
        int s_len = strlen(s);
        if (s == NULL || s_len == 0) {
                return "";
        }

        int start = 0, end = 0;
        for (int i = 0; i < s_len; i++) {
                int len1 = expendAroundCenter(s, i, i);
                int len2 = expendAroundCenter(s, i, i + 1);

                int len = MAX(len1, len2);
                if (len > end - start) {
                        start = i - (len - 1) / 2;
                        end = i + len / 2;
                }
        }
        s += start;
        size_t _size = sizeof(char) * (end - start + 2);
        char *ans = malloc(_size);

        memset(ans, 0, _size);
        strncpy(ans, s, _size - 1);

        return ans;
}

int main() {
        char *ans = longestPalindrome("cbbd");
        puts(ans);
        free(ans);
        return 0;
}