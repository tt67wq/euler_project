#!/usr/bin/env python
# -*- coding: utf-8 -*-

from typing import List
import unittest

# 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

# 示例 1：

# 输入：nums = [1,2,3]
# 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
# 示例 2：

# 输入：nums = [0,1]
# 输出：[[0,1],[1,0]]
# 示例 3：

# 输入：nums = [1]
# 输出：[[1]]


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        res = []

        def dfs(x):
            if x == len(nums) - 1:
                res.append(nums[:])
                return
            for i in range(x, len(nums)):
                nums[i], nums[x] = nums[x], nums[i]
                dfs(x + 1)
                nums[i], nums[x] = nums[x], nums[i]

        dfs(0)
        return res


class TestPermute(unittest.TestCase):

    def test_permute(self):
        self.list_equal(Solution().permute([]), [])
        self.list_equal(Solution().permute([1]), [[1]])
        self.list_equal(Solution().permute([1, 2]), [[1, 2], [2, 1]])
        self.list_equal(
            Solution().permute([1, 2, 3]),
            [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]],
        )
        self.assertEqual(
            Solution().permute([1, 1, 2]),
            [[1, 1, 2], [1, 2, 1], [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 1, 1]],
        )

    def list_equal(self, list1, list2):
        if len(list1) != len(list2):
            return False
        # sort
        list1.sort()
        list2.sort()
        for i in range(len(list1)):
            if list1[i] != list2[i]:
                return False
        return True


def main():
    unittest.main()


if __name__ == "__main__":
    main()
