#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def longestConsecutive(self, nums):

        parents = {}

        for num in nums:
            parents[num] = num

        for num in nums:
            if parents.get(num - 1):
                parents[num - 1] = num
            if parents.get(num + 1):
                parents[num] = num + 1

        ans = 0
        for num in nums:
            tmp = self.find(parents, num) - num + 1
            if tmp > ans:
                ans = tmp
        return ans

    def find(self, parents, num):
        if parents.get(num) != num:
            parents[num] = self.find(parents, parents.get(num))
        return parents[num]


def main():
    s = Solution()
    print(s.longestConsecutive([100, 4, 200, 1, 3, 2]))


if __name__ == '__main__':
    main()
