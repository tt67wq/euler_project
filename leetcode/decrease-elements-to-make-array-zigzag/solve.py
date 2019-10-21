#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


import copy
UP = 0
DOWN = 1
CACHE = {}


class Solution:
    def movesToMakeZigzag(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        global CACHE
        CACHE = {}
        ns = copy.deepcopy(nums)

        return min(self.zigzag(nums, 0, UP), self.zigzag(ns, 0, DOWN))

    def zigzag(self, nums, index, flag):
        if index == len(nums)-1:
            return 0

        global CACHE

        fp = "{}:{}".format(index, flag)
        if CACHE.get(fp):
            return CACHE[fp]

        res = 0
        if flag == UP:
            if nums[index] < nums[index + 1]:
                res = self.zigzag(nums, index + 1, DOWN)
            else:
                d = nums[index] + 1 - nums[index + 1]
                nums[index] -= d
                res = self.zigzag(nums, index + 1, DOWN) + d
        else:
            if nums[index] <= nums[index + 1]:
                d = nums[index + 1] - nums[index] + 1
                nums[index + 1] -= d
                res = self.zigzag(nums, index + 1, UP) + d
            else:
                res = self.zigzag(nums, index + 1, UP)

        CACHE[fp] = res
        return res


def main():
    s = Solution()
    while 1:
        print(s.movesToMakeZigzag([int(x) for x in input().split(",")]))


if __name__ == '__main__':
    main()
