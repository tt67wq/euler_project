/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-06-08
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

// 有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

// 每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <=
// y。那么粉碎的可能结果如下：

// 如果 x == y，那么两块石头都会被完全粉碎；
// 如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
// 最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。

//  

// 示例 1：

// 输入：stones = [2,7,4,1,8,1]
// 输出：1
// 解释：
// 组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
// 组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
// 组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
// 组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
// 示例 2：

// 输入：stones = [31,26,33,21,40]
// 输出：5
// 示例 3：

// 输入：stones = [1,2]
// 输出：1
//  

// 提示：

// 1 <= stones.length <= 30
// 1 <= stones[i] <= 100

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/last-stone-weight-ii
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// class Solution {
//     public int lastStoneWeightII(int[] stones) {
//         int sum = 0;
//         for (int weight : stones) {
//             sum += weight;
//         }
//         int n = stones.length, m = sum / 2;
//         boolean[][] dp = new boolean[n + 1][m + 1];
//         dp[0][0] = true;
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j <= m; ++j) {
//                 if (j < stones[i]) {
//                     dp[i + 1][j] = dp[i][j];
//                 } else {
//                     dp[i + 1][j] = dp[i][j] || dp[i][j - stones[i]];
//                 }
//             }
//         }
//         for (int j = m;; --j) {
//             if (dp[n][j]) {
//                 return sum - 2 * j;
//             }
//         }
//     }
// }

int lastStoneWeightII(int *stones, int stonesSize) {
        int sum = 0;
        for (int i = 0; i < stonesSize; i++) {
                sum += stones[i];
        }

        int mid = sum >> 1;

        // dp[i+1][j] => 前 i 个石头能否凑出重量 j
        bool **dp = (bool **)malloc((stonesSize + 1) * sizeof(bool *));
        for (int i = 0; i < stonesSize + 1; i++) {
                dp[i] = (bool *)calloc(mid + 1, sizeof(bool));
        }

        dp[0][0] = true;

        for (int i = 0; i < stonesSize; i++) {
                for (int j = 0; j <= mid; j++) {
                        if (j < stones[i]) {
                                dp[i + 1][j] = dp[i][j];
                        } else {
                                dp[i + 1][j] = dp[i][j] || dp[i][j - stones[i]];
                        }
                }
        }

        for (int i = mid; i >= 0; i--) {
                if (dp[stonesSize][i]) {
                        return sum - 2 * i;
                }
        }
        return -1;
}

int main() {
        int stones[] = {2, 7, 4, 1, 8, 1};

        int ans = lastStoneWeightII(stones, sizeof(stones) / sizeof(int));
        printf("%d\n", ans);

        return 0;
}