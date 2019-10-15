#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "https://leetcode-cn.com/problems/largest-divisible-subset/"


class Solution(object):
    def largestDivisibleSubset(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """

        if not nums:
            return nums
        if len(nums) == 1:
            return nums
        l = len(nums)
        nums.sort()

        dp = [[i] for i in nums]

        for i in range(1, l):
            for j in range(0, i):
                if nums[i] % nums[j] == 0:
                    dp[i] = max(dp[j] + [nums[i]], dp[i], key=len)

        return max(dp, key=len)


def main():
    pass


if __name__ == '__main__':
    main()
