/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-08-17
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

// 二进制数转字符串。给定一个介于0和1之间的实数（如0.72），类型为double，
// 打印它的二进制表达式。如果该数字无法精确地用32位以内的二进制表示，则打印“ERROR”。

// 示例1:

//  输入：0.625
//  输出："0.101"
// 示例2:

//  输入：0.1
//  输出："ERROR"
//  提示：0.1无法被二进制准确表示
// 提示：

// 32位包括输出中的"0."这两位。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/bianry-number-to-string-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

typedef struct cache {
        char val[50];
        UT_hash_handle hh;
} cache;

char *printBin(double num) {
        cache *cs = NULL;
        char *ans = (char *)calloc(100, sizeof(char));
        int idx = 0;
        ans[idx++] = '0';
        ans[idx++] = '.';

        while (idx < 32) {
                cache *c;
                char val[50] = {0};
                snprintf(val, 50, "%f", num);
                // puts(val);
                HASH_FIND_STR(cs, val, c);
                if (c) {
                        return "ERROR";
                } else {
                        c = (cache *)malloc(sizeof(*c));
                        snprintf(c->val, 50, "%f", num);
                        HASH_ADD_STR(cs, val, c);
                }
                num *= 2;
                if (num >= 1) {
                        ans[idx++] = '1';
                        num -= 1;
                } else if (num > 0) {
                        ans[idx++] = '0';
                } else {
                        break;
                }
        }
        if (idx == 32) {
                return "ERROR";
        }
        ans[idx] = '\0';
        return ans;
}

int main() {
        printf("%s\n", printBin(0.573628));
        return 0;
}