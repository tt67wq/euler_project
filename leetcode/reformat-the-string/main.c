/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-19
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

// 给你一个混合了数字和字母的字符串 s，其中的字母均为小写英文字母。

// 请你将该字符串重新格式化，使得任意两个相邻字符的类型都不同。也就是说，字母后面应该跟着数字，而数字后面应该跟着字母。

// 请你返回 重新格式化后 的字符串；如果无法按要求重新格式化，则返回一个 空字符串 。

//  

// 示例 1：

// 输入：s = "a0b1c2"
// 输出："0a1b2c"
// 解释："0a1b2c" 中任意两个相邻字符的类型都不同。 "a0b1c2", "0a1b2c", "0c2a1b"
// 也是满足题目要求的答案。 示例 2：

// 输入：s = "leetcode"
// 输出：""
// 解释："leetcode" 中只有字母，所以无法满足重新格式化的条件。
// 示例 3：

// 输入：s = "1229857369"
// 输出：""
// 解释："1229857369" 中只有数字，所以无法满足重新格式化的条件。
// 示例 4：

// 输入：s = "covid2019"
// 输出："c2o0v1i9d"
// 示例 5：

// 输入：s = "ab123"
// 输出："1a2b3"
//  

// 提示：

// 1 <= s.length <= 500
// s 仅由小写英文字母和/或数字组成。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/reformat-the-string
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define ABS(n) ((n) > 0 ? (n) : -(n))

char *reformat(char *s) {
        int l = strlen(s);
        char *nums = (char *)malloc(sizeof(char) * (l + 1));
        char *letters = (char *)malloc(sizeof(char) * (l + 1));
        int nc = 0, lc = 0;

        for (int i = 0; i < l; i++) {
                if (s[i] >= '0' && s[i] <= '9') {
                        nums[nc++] = s[i];
                } else {
                        letters[lc++] = s[i];
                }
        }
        if (ABS(nc - lc) > 1) {
                return "";
        }
        char *ans = (char *)malloc(sizeof(char) * (l + 1));
        char *ansp = ans;
        int j = 0, k = 0;
        if (nc < lc) {
                while (j < nc && k < lc) {
                        (*(ansp++)) = letters[k++];
                        (*(ansp++)) = nums[j++];
                }
                *(ansp++) = letters[k];
        } else if (nc > lc) {
                while (j < nc && k < lc) {
                        (*(ansp++)) = nums[j++];
                        (*(ansp++)) = letters[k++];
                }
                *(ansp++) = nums[j];
        } else {
                while (j < nc && k < lc) {
                        (*(ansp++)) = nums[j++];
                        (*(ansp++)) = letters[k++];
                }
        }
        *ansp = '\0';
        return ans;
}

int main() {
        char s[] = "a0b1c2";
        puts(reformat(s));
        return 0;
}