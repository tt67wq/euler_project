/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-11-01
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 给你两个字符串数组 word1 和 word2 。如果两个数组表示的字符串相同，返回 true ；否则，返回 false 。

// 数组表示的字符串 是由数组中的所有元素 按顺序 连接形成的字符串。

//  

// 示例 1：

// 输入：word1 = ["ab", "c"], word2 = ["a", "bc"]
// 输出：true
// 解释：
// word1 表示的字符串为 "ab" + "c" -> "abc"
// word2 表示的字符串为 "a" + "bc" -> "abc"
// 两个字符串相同，返回 true
// 示例 2：

// 输入：word1 = ["a", "cb"], word2 = ["ab", "c"]
// 输出：false
// 示例 3：

// 输入：word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
// 输出：true
//  

// 提示：

// 1 <= word1.length, word2.length <= 103
// 1 <= word1[i].length, word2[i].length <= 103
// 1 <= sum(word1[i].length), sum(word2[i].length) <= 103
// word1[i] 和 word2[i] 由小写字母组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/check-if-two-string-arrays-are-equivalent
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

bool arrayStringsAreEqual(char **word1, int word1Size, char **word2, int word2Size) {
        int i = 0, j = 0;
        bool switch1 = true, switch2 = true;
        char *currentWord1, *currentWord2;
        while (i < word1Size && j < word2Size) {
                if (switch1) {
                        currentWord1 = word1[i];
                        switch1 = false;
                }
                if (switch2) {
                        currentWord2 = word2[j];
                        switch2 = false;
                }
                while (*currentWord1 != '\0' && *currentWord2 != '\0') {
                        if (*currentWord1 == *currentWord2) {
                                currentWord1++;
                                currentWord2++;
                        } else {
                                return false;
                        }
                }
                if (*currentWord1 == '\0') {
                        i++;
                        switch1 = true;
                }
                if (*currentWord2 == '\0') {
                        j++;
                        switch2 = true;
                }
        }
        if (switch1 && switch2 && i == word1Size && j == word2Size)
                return true;
        return false;
}

int main() {
        char *word1[] = {"a"};
        char *word2[] = {"a", "b"};
        printf("%d\n", arrayStringsAreEqual(word1, 1, word2, 2));
        return 0;
}