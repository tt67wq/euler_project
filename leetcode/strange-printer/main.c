/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-05-25
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 有台奇怪的打印机有以下两个特殊要求：

// 打印机每次只能打印由 同一个字符 组成的序列。
// 每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。
// 给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数。

//  
// 示例 1：

// 输入：s = "aaabbb"
// 输出：2
// 解释：首先打印 "aaa" 然后打印 "bbb"。
// 示例 2：

// 输入：s = "aba"
// 输出：2
// 解释：首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 'a'。
//  

// 提示：

// 1 <= s.length <= 100
// s 由小写英文字母组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/strange-printer
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int strangePrinter(char *s) {
        int sLen = strlen(s);
        // dp[i][j] = strangePrinter(s[i:j])
        int **dp = (int **)calloc(sLen, sizeof(int *));
        for (int i = 0; i < sLen; i++) {
                dp[i] = (int *)calloc(sLen, sizeof(int));
        }

        for (int i = sLen - 1; i >= 0; i--) {
                dp[i][i] = 1;
                for (int j = i + 1; j < sLen; j++) {
                        if (s[i] == s[j]) {
                                dp[i][j] = dp[i][j - 1];
                        } else {
                                int min = INT32_MAX;
                                for (int k = i; k < j; k++) {
                                        int _tmp = dp[i][k] + dp[k + 1][j];
                                        min = min < _tmp ? min : _tmp;
                                }
                                dp[i][j] = min;
                        }
                }
        }
        return dp[0][sLen - 1];
}

int main() {
        int ans = strangePrinter("aba");
        printf("%d\n", ans);
        return 0;
}