/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-11-03
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

// 给你一个字符串 sequence ，如果字符串 word 连续重复 k 次形成的字符串是 sequence
// 的一个子字符串，那么单词 word 的 重复值为 k 。 单词 word 的 最大重复值 是单词 word 在 sequence
// 中最大的重复值。如果 word 不是 sequence 的子串，那么重复值 k 为 0 。

// 给你一个字符串 sequence 和 word ，请你返回 最大重复值 k 。

// 示例 1：

// 输入：sequence = "ababc", word = "ab"
// 输出：2
// 解释："abab" 是 "ababc" 的子字符串。
// 示例 2：

// 输入：sequence = "ababc", word = "ba"
// 输出：1
// 解释："ba" 是 "ababc" 的子字符串，但 "baba" 不是 "ababc" 的子字符串。
// 示例 3：

// 输入：sequence = "ababc", word = "ac"
// 输出：0
// 解释："ac" 不是 "ababc" 的子字符串。

int maxRepeating(char *sequence, char *word) {
        int ans = 0, sl = strlen(sequence), wl = strlen(word);
        char *a = (char *)calloc(sl + 1, sizeof(char));
        while (strlen(a) + wl <= sl) {
                strcat(a, word);
                if (strstr(sequence, a) != NULL) {
                        ans++;
                }
        }
        return ans;
}

int main() {
        char a[] = "a", b[] = "a";
        printf("%d\n", maxRepeating(a, b));
        return 0;
}