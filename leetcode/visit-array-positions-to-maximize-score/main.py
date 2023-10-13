#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/visit-array-positions-to-maximize-score/


# 给你一个下标从 0 开始的整数数组 nums 和一个正整数 x 。

# 你 一开始 在数组的位置 0 处，你可以按照下述规则访问数组中的其他位置：

# 如果你当前在位置 i ，那么你可以移动到满足 i < j 的 任意 位置 j 。
# 对于你访问的位置 i ，你可以获得分数 nums[i] 。
# 如果你从位置 i 移动到位置 j 且 nums[i] 和 nums[j] 的 奇偶性 不同，那么你将失去分数 x 。
# 请你返回你能得到的 最大 得分之和。

# 注意 ，你一开始的分数为 nums[0] 。


# 示例 1：

# 输入：nums = [2,3,6,1,9,2], x = 5
# 输出：13
# 解释：我们可以按顺序访问数组中的位置：0 -> 2 -> 3 -> 4 。
# 对应位置的值为 2 ，6 ，1 和 9 。因为 6 和 1 的奇偶性不同，所以下标从 2 -> 3 让你失去 x = 5 分。
# 总得分为：2 + 6 + 1 + 9 - 5 = 13 。
# 示例 2：

# 输入：nums = [2,4,6,8], x = 3
# 输出：20
# 解释：数组中的所有元素奇偶性都一样，所以我们可以将每个元素都访问一次，而且不会失去任何分数。
# 总得分为：2 + 4 + 6 + 8 = 20 。

from typing import List


class Solution:
    def maxScore(self, nums: List[int], x: int) -> int:
        # dp[i] => maxScore(nums[:i], x)
        # dp[i][0] => maxScore(nums[:i], x) 且 上次访问的 为奇数
        # dp[i][1] => maxScore(nums[:i], x) 且 上次访问的 为偶数
        dp = [[0, 0] for _ in range(len(nums))]
        for i, n in enumerate(nums):
            if i > 0:
                if n & 1:
                    dp[i][0] = max(dp[i - 1][0] + n, dp[i - 1][1] + n - x)
                    dp[i][1] = dp[i - 1][1]
                else:
                    dp[i][1] = max(dp[i - 1][1] + n, dp[i - 1][0] + n - x)
                    dp[i][0] = dp[i - 1][0]
            else:
                if n & 1:
                    dp[0][0] = n
                    dp[0][1] = n - x
                else:
                    dp[0][1] = n
                    dp[0][0] = n - x
        return max(dp[-1])


def test_maxScore():
    s = Solution()

    # Test case 1
    nums1 = [2, 3, 6, 1, 9, 2]
    x1 = 5
    expected1 = 13
    assert s.maxScore(nums1, x1) == expected1

    # Test case 2
    nums2 = [2, 4, 6, 8]
    x2 = 3
    expected2 = 20
    assert s.maxScore(nums2, x2) == expected2

    # Test case 3
    nums3 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    x3 = 5
    expected3 = 40
    assert s.maxScore(nums3, x3) == expected3

    # Test case 4
    nums4 = [1, 3, 5, 7, 9]
    x4 = 2
    expected4 = 24
    assert s.maxScore(nums4, x4) == expected4

    # Test case 5
    nums5 = [2, 4, 6, 8, 10]
    x5 = 1
    expected5 = 30
    assert s.maxScore(nums5, x5) == expected5

    print("All test cases pass")


def main():
    test_maxScore()


if __name__ == "__main__":
    main()
