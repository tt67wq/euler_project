/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2022-11-02
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
// 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i
// 小的那个的概率。

// 示例 1:

// 输入: 1
// 输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
// 示例 2:

// 输入: 2
// 输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]
//  

// 限制：

// 1 <= n <= 11

// 来源：力扣（LeetCode）
// 链接：https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *dicesProbability(int n, int *returnSize) {
        int dpLen = 6;
        double *dp = (double *)calloc(dpLen, sizeof(double));
        for (int i = 0; i < dpLen; i++) {
                dp[i] = 1.0 / 6.0;
        }
        //
        for (int i = 2; i <= n; i++) {
                double *tmp = (double *)calloc(dpLen + 5, sizeof(double));
                for (int j = 0; j < dpLen; j++) {
                        for (int k = 1; k <= 6; k++) {
                                tmp[j + k - 1] += dp[j] / 6.0;
                        }
                }
                double *old = dp;
                dp = tmp;
                free(old);
                dpLen += 5;
        }
        *returnSize = dpLen;
        return dp;
}

int main() {
        int returnSize;
        double *ans = dicesProbability(2, &returnSize);
        for (int i = 0; i < returnSize; i++) {
                printf("%.6f ", ans[i]);
        }
        puts("");
        return 0;
}