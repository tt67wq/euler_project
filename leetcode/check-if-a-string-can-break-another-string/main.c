/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-27
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
#include <string.h>

// 给你两个字符串 s1 和 s2 ，它们长度相等，请你检查是否存在一个 s1  的排列可以打破 s2 的一个排列，
// 或者是否存在一个 s2 的排列可以打破 s1 的一个排列。

// 字符串 x 可以打破字符串 y （两者长度都为 n ）需满足对于所有 i（在 0 到 n - 1 之间）都有 x[i] >=
// y[i]（字典序意义下的顺序）。

// 示例 1：

// 输入：s1 = "abc", s2 = "xya"
// 输出：true
// 解释："ayx" 是 s2="xya" 的一个排列，"abc" 是字符串 s1="abc" 的一个排列，且 "ayx" 可以打破 "abc"
// 。 示例 2：

// 输入：s1 = "abe", s2 = "acd"
// 输出：false
// 解释：s1="abe" 的所有排列包括："abe"，"aeb"，"bae"，"bea"，"eab" 和 "eba" ，s2="acd"
// 的所有排列包括："acd"，"adc"，"cad"，"cda"，"dac" 和 "dca"。然而没有任何 s1 的排列可以打破 s2
// 的排列。也没有 s2 的排列能打破 s1 的排列。 示例 3：

// 输入：s1 = "leetcodee", s2 = "interview"
// 输出：true
//  

// 提示：

// s1.length == n
// s2.length == n
// 1 <= n <= 10^5
// 所有字符串都只包含小写英文字母。

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/check-if-a-string-can-break-another-string
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int cmpfunc(const void *a, const void *b) { return *(char *)a - *(char *)b; }
bool checkIfCanBreak(char *s1, char *s2) {
        qsort(s1, strlen(s1), sizeof(char), cmpfunc);
        qsort(s2, strlen(s2), sizeof(char), cmpfunc);

        int flag = 0;
        for (int i = 0; i < strlen(s1); i++) {
                if (s1[i] == s2[i])
                        continue;
                int t = s1[i] > s2[i] ? 1 : -1;
                if (flag != 0 && t != flag) {
                        return false;
                }
                flag = t;
        }
        return true;
}

int main() {
        char s1[] = "yopumzgd";
        char s2[] = "pamntyya";
        printf("%d\n", checkIfCanBreak(s1, s2));
        return 0;
}