/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-15
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// 你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈
// ， 这意味着第一个房屋和最后一个房屋是紧挨着的。
// 同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

// 给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下
// ，能够偷窃到的最高金额。

//  

// 示例 1：

// 输入：nums = [2,3,2]
// 输出：3
// 解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
// 示例 2：

// 输入：nums = [1,2,3,1]
// 输出：4
// 解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
//      偷窃到的最高金额 = 1 + 3 = 4 。
// 示例 3：

// 输入：nums = [0]
// 输出：0
//  

// 提示：

// 1 <= nums.length <= 100
// 0 <= nums[i] <= 1000

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/house-robber-ii
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int rob(int *nums, int numsSize) {
        if (numsSize == 0) {
                return 0;
        }
        if (numsSize == 1) {
                return nums[0];
        }
        if (numsSize == 2) {
                return MAX(nums[0], nums[1]);
        }

        // dp[i]: max amount you can steal in nums[:i)
        int *dp1 = (int *)malloc(sizeof(int) * (numsSize + 1));
        int *dp2 = (int *)malloc(sizeof(int) * (numsSize + 1));
        int *dp3 = (int *)malloc(sizeof(int) * (numsSize + 1));

        dp1[0] = 0;
        dp1[1] = nums[0];
        dp1[2] = nums[0];

        dp2[0] = 0;
        dp2[1] = 0;
        dp2[2] = nums[1];
        dp2[3] = nums[1];

        dp3[0] = 0;
        dp3[1] = 0;
        dp3[2] = 0;
        dp3[3] = nums[2];

        for (int i = 3; i < numsSize; i++) {
                dp1[i] = MAX(dp1[i - 1], dp1[i - 2] + nums[i - 1]);
        }

        for (int i = 4; i <= numsSize; i++) {
                dp2[i] = MAX(dp2[i - 1], dp2[i - 2] + nums[i - 1]);
        }

        for (int i = 5; i <= numsSize; i++) {
                dp3[i] = MAX(dp3[i - 1], dp3[i - 2] + nums[i - 1]);
        }

        return MAX(MAX(dp1[numsSize - 1], dp2[numsSize]), dp3[numsSize]);
}

int main() {
        int nums[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        int ans = rob(nums, NELEMS(nums));
        printf("%d\n", ans);
        return 0;
}