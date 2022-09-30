/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-09-30
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

// 字符串轮转。给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成（比如，waterbottle是erbottlewat旋转后的字符串）。

// 示例1:

//  输入：s1 = "waterbottle", s2 = "erbottlewat"
//  输出：True
// 示例2:

//  输入：s1 = "aa", s2 = "aba"
//  输出：False
// 提示：

// 字符串长度在[0, 100000]范围内。
// 说明:

// 你能只调用一次检查子串的方法吗？

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/string-rotation-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

bool isFlipedString(char *s1, char *s2) {
        int l1 = strlen(s1);
        int l2 = strlen(s2);
        if (l1 != l2)
                return false;

        char s3[200000] = {0};
        strcpy(s3, s1);
        strcat(s3, s1);

        if (strstr(s3, s2) != NULL) {
                return true;
        }
        return false;
}
