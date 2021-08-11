/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-08-11
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

// 给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2
// 的乘积，它们的乘积也表示为字符串形式。

// 示例 1:

// 输入: num1 = "2", num2 = "3"
// 输出: "6"
// 示例 2:

// 输入: num1 = "123", num2 = "456"
// 输出: "56088"
// 说明：

// num1 和 num2 的长度小于110。
// num1 和 num2 只包含数字 0-9。
// num1 和 num2 均不以零开头，除非是数字 0 本身。
// 不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。
// 通过次数158,207提交次数352,737

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/multiply-strings
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

void multi_one(char *num, char m, int offset, int *max, int **res) {
        int l = strlen(num);
        // int *res = (int *)calloc(MAX, sizeof(int));
        int *_res = *res;

        int idx = offset, d = 0;
        for (int i = l - 1; i >= 0; i--) {
                int s = (num[i] - '0') * (m - '0') + d;
                _res[idx++] = s % 10;
                d = s / 10;
        }
        if (d) {
                _res[idx++] = d;
        }
        *max = *max > idx ? *max : idx;
}

char *multiply(char *num1, char *num2) {
        int l1 = strlen(num1), l2 = strlen(num2), ms = 0;

        int **rs = (int **)malloc(l2 * sizeof(int *));
        char *ans = (char *)calloc(l1 + l2 + 1, sizeof(char));
        for (int i = l2 - 1; i >= 0; i--) {
                rs[i] = (int *)calloc(l1 + l2 + 1, sizeof(int));
                multi_one(num1, num2[i], l2 - 1 - i, &ms, &(rs[i]));
        }

        int d = 0;
        for (int i = 0; i < ms; i++) {
                int _s = d;
                for (int j = 0; j < l2; j++) {
                        _s += rs[j][i];
                }
                ans[i] = _s % 10 + '0';
                d = _s / 10;
        }
        if (d) {
                ans[ms++] = d + '0';
        }

        // reverse
        for (int i = 0; i <= (ms - 1) / 2; i++) {
                char temp = ans[i];
                ans[i] = ans[ms - 1 - i];
                ans[ms - 1 - i] = temp;
        }
        if (ans[0] == '0') {
                return "0";
        }
        ans[ms] = '\0';
        return ans;
}

int main() {
        char num1[] = "140";
        char num2[] = "721";

        puts(multiply(num1, num2));

        return 0;
}