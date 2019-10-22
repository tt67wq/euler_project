#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


class Solution:
    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        l = len(nums)
        if l <= 1:
            return 0

        start = 0
        reach = 0
        step = 0
        while reach < l - 1:
            farest = 0
            for i in range(start, reach+1):
                farest = max(farest, nums[i]+i)
            start = reach+1
            reach = farest
            step += 1
        return step


def main():
    s = Solution()
    print(s.jump([2, 3, 1, 1, 4]))


if __name__ == '__main__':
    main()
