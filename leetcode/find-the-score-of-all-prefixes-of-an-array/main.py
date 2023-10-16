#!/usr/bin/env python
# -*- coding: utf-8 -*-

from typing import List

# https://leetcode.cn/problems/find-the-score-of-all-prefixes-of-an-array/


class Solution:
    def findPrefixScore(self, nums: List[int]) -> List[int]:
        if len(nums) == 0:
            return []

        conver = [0] * len(nums)
        maxs = [0] * len(nums)
        conver[0] = nums[0] * 2
        maxs[0] = nums[0]
        for i in range(1, len(nums)):
            if nums[i] > maxs[i - 1]:
                maxs[i] = nums[i]
                conver[i] = nums[i] + maxs[i]
            else:
                maxs[i] = maxs[i - 1]
                conver[i] = maxs[i - 1] + nums[i]

        ans = [0] * len(nums)
        ans[0] = conver[0]
        for i in range(1, len(nums)):
            ans[i] = ans[i - 1] + conver[i]
        return ans


def test_findPrefixScore():
    s = Solution()

    # Test case 1
    nums1 = [2, 3, 7, 5, 10]
    expected1 = [4, 10, 24, 36, 56]
    assert s.findPrefixScore(nums1) == expected1

    # Test case 2
    nums2 = [1, 1, 2, 4, 8, 16]
    expected2 = [2, 4, 8, 16, 32, 64]
    assert s.findPrefixScore(nums2) == expected2

    print("All test cases pass")


def main():
    test_findPrefixScore()


if __name__ == "__main__":
    main()
