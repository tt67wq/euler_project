/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-17
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

// 有效数字（按顺序）可以分成以下几个部分：

// 一个 小数 或者 整数
// （可选）一个 'e' 或 'E' ，后面跟着一个 整数

// 小数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 下述格式之一：
// 至少一位数字，后面跟着一个点 '.'
// 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
// 一个点 '.' ，后面跟着至少一位数字

// 整数（按顺序）可以分成以下几个部分：
// （可选）一个符号字符（'+' 或 '-'）
// 至少一位数字
// 部分有效数字列举如下：

// ["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93",
// "-123.456e789"] 部分无效数字列举如下：

// ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]
// 给你一个字符串 s ，如果 s 是一个 有效数字 ，请返回 true 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/valid-number
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

bool _isInteger(const char *s) {
        int l = strlen(s);
        if (l == 0) {
                return false;
        }
        for (int i = 0; i < l; i++) {
                if (s[i] >= '0' && s[i] <= '9') {
                } else {
                        return false;
                }
        }
        return true;
}

bool isInteger(const char *s) {
        if (strlen(s) > 0 && (s[0] == '+' || s[0] == '-')) {
                return _isInteger(s + 1);
        }

        return _isInteger(s);
}

bool isFloat(const char *s) {
        int l = strlen(s);
        if (l == 0) {
                return false;
        }
        if (s[0] == '+' || s[0] == '-') {
                return isFloat(s + 1);
        }

        // 至少一位数字，后面跟着一个点 '.'
        // 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
        // 一个点 '.' ，后面跟着至少一位数字

        char *_f = strchr(s, '.');
        if (_f == NULL) {
                return false;
        }

        // 一个点 '.' ，后面跟着至少一位数字
        if (l == strlen(_f)) {
                return _isInteger(_f + 1);
        }

        char *pre = (char *)calloc(l, sizeof(char));
        strncpy(pre, s, l - strlen(_f));

        // 至少一位数字，后面跟着一个点 '.'
        if (strlen(_f + 1) == 0) {
                return _isInteger(pre);
        } else {
                return _isInteger(pre) && _isInteger(_f + 1);
        }
}

bool isNumber(char *s) {
        char *e;
        e = strchr(s, 'e');
        if (e == NULL) {
                e = strchr(s, 'E');
        }
        if (e == NULL) {
                return isInteger(s) || isFloat(s);
        }

        char *pre = (char *)calloc(strlen(s), sizeof(char));
        strncpy(pre, s, strlen(s) - strlen(e));

        return (isInteger(pre) || isFloat(pre)) && isInteger(e + 1);
}

int main() {
        char *s[] = {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"};

        for (int i = 0; i < 8; i++) {
                printf("%s, %d\n", s[i], isNumber(s[i]));
        }

        return 0;
}