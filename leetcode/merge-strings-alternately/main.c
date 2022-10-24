/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-10-24
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

// 给你两个字符串 word1 和 word2 。请你从 word1 开始，通过交替添加字母来合并字符串。
// 如果一个字符串比另一个字符串长，就将多出来的字母追加到合并后字符串的末尾。

// 返回 合并后的字符串 。

//  

// 示例 1：

// 输入：word1 = "abc", word2 = "pqr"
// 输出："apbqcr"
// 解释：字符串合并情况如下所示：
// word1：  a   b   c
// word2：    p   q   r
// 合并后：  a p b q c r
// 示例 2：

// 输入：word1 = "ab", word2 = "pqrs"
// 输出："apbqrs"
// 解释：注意，word2 比 word1 长，"rs" 需要追加到合并后字符串的末尾。
// word1：  a   b
// word2：    p   q   r   s
// 合并后：  a p b q   r   s
// 示例 3：

// 输入：word1 = "abcd", word2 = "pq"
// 输出："apbqcd"
// 解释：注意，word1 比 word2 长，"cd" 需要追加到合并后字符串的末尾。
// word1：  a   b   c   d
// word2：    p   q
// 合并后：  a p b q c   d
//  

// 提示：

// 1 <= word1.length, word2.length <= 100
// word1 和 word2 由小写英文字母组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/merge-strings-alternately
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

char *mergeAlternately(char *word1, char *word2) {
        int l1 = strlen(word1), l2 = strlen(word2);
        char *ans = (char *)calloc(l1 + l2 + 1, sizeof(char));
        char *p1 = word1, *p2 = word2, *ansp = ans;
        bool b = true;
        while (*p1 != '\0' && *p2 != '\0') {
                char **p = b ? &p1 : &p2;
                *ansp = **p;
                b = !b;
                (*p)++;
                ansp++;
        }
        if (*p1 == '\0') {
                strcat(ans, p2);
        } else {
                strcat(ans, p1);
        }
        return ans;
}

int main() {
        char word1[] = "abcd", word2[] = "pq";
        puts(mergeAlternately(word1, word2));
        return 0;
}