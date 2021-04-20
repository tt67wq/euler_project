/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-20
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

// 实现 strStr() 函数。

// 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle
// 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

//  

// 说明：

// 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

// 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java
// 的 indexOf() 定义相符。

//  

// 示例 1：

// 输入：haystack = "hello", needle = "ll"
// 输出：2
// 示例 2：

// 输入：haystack = "aaaaa", needle = "bba"
// 输出：-1
// 示例 3：

// 输入：haystack = "", needle = ""
// 输出：0
//  

// 提示：

// 0 <= haystack.length, needle.length <= 5 * 104
// haystack 和 needle 仅由小写英文字符组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/implement-strstr
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

void genNext(char *needle, int *next) {
        next[0] = -1;
        int i = 0, j = -1;
        while (i < strlen(needle)) {
                if (j == -1 || needle[i] == needle[j]) {
                        ++i;
                        ++j;
                        next[i] = j;
                } else {
                        j = next[j];
                }
        }
}

int strStr(char *haystack, char *needle) {
        if (strlen(needle) == 0) {
                return 0;
        }
        int *next = (int *)malloc(sizeof(int) * (strlen(needle) + 1));
        genNext(needle, next);
        int i = 0, j = 0;
        int lh = strlen(haystack), ln = strlen(needle);
        while (i < lh && j < ln) {
                if (j == -1 || haystack[i] == needle[j]) {
                        i++;
                        j++;
                } else {
                        j = next[j];
                }
        }
        if (j == ln) {
                return i - j;
        }
        return -1;
}

int main() {
        char a[] = "hello";
        char b[] = "ll";
        printf("%d\n", strStr(a, b));
        return 0;
}