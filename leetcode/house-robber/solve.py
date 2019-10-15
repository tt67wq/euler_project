#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "https://leetcode-cn.com/problems/house-robber/"
import hashlib
CACHE = {}


class Solution(object):
    def fp(self, nums):
        s = ",".join([str(x) for x in nums]).encode()
        return hashlib.md5(s).hexdigest()

    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if sum(nums) == 0:
            return 0
        if len(nums) == 0:
            return 0

        if len(nums) == 1:
            return nums[0]

        if len(nums) == 2:
            return max(nums)

        p = self.fp(nums)
        if CACHE.get(p):
            return CACHE[p]

        res = max(nums[0]+self.rob(nums[2:]), nums[1]+self.rob(nums[3:]))
        CACHE[p] = res
        return res


def main():
    pass


if __name__ == '__main__':
    main()
