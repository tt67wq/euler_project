/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-07
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 三步问题。有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。
// 实现一种方法，计算小孩有多少种上楼梯的方式。结果可能很大，你需要对结果模1000000007。

// 示例1:

//  输入：n = 3
//  输出：4
//  说明: 有四种走法
// 示例2:

//  输入：n = 5
//  输出：13
// 提示:

// n范围在[1, 1000000]之间

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/three-steps-problem-lcci
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define MOD 1000000007
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int waysToStep(int n) {
        long *dp =
            (long *)malloc(sizeof(long) * MAX(4, n + 1)); // dp[i] how many way to reach step n

        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;

        for (int i = 3; i <= n; i++) {
                dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
                dp[i] %= MOD;
        }
        return (int)dp[n];
}

int main() {
        printf("%d\n", waysToStep(5));
        return 0;
}