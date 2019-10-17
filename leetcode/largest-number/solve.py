#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: ""


# https://leetcode-cn.com/problems/largest-number/

from functools import cmp_to_key


class Solution:

    # a > b?
    def cmp(self, a, b):
        if a == b:
            return 0
        i = 0
        while i < len(a) and i < len(b):
            if a[i] == b[i]:
                i += 1
                continue
            if a[i] > b[i]:
                return 1
            else:
                return -1

        if i == len(a):
            return self.cmp(a, b[i:])
        else:
            return self.cmp(a[i:], b)

    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        key = cmp_to_key(lambda x, y: self.cmp(x, y))
        res = "".join(sorted([str(n) for n in nums], key=key)[::-1])
        if res.startswith("0"):
            return "0"
        else:
            return res


def main():
    s = Solution()
    while 1:
        ls = input()
        print(s.largestNumber([int(e) for e in ls.split(",")]))


if __name__ == '__main__':
    main()
