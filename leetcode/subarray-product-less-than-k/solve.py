#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# author: wq
# description: "https://leetcode-cn.com/problems/subarray-product-less-than-k/"


class Solution:
    def numSubarrayProductLessThanK(self, nums, k):

        res = 0
        i = 0
        j = 0
        acc = 1
        l = len(nums)
        while i < l:
            while j < l and acc * nums[j] < k:
                acc *= nums[j]
                j += 1

            if j == i:
                i += 1
                j += 1
            else:
                res += (j-i)
                acc //= nums[i]
                i += 1

        return res


def main():
    s = Solution()
    print(s.numSubarrayProductLessThanK([10, 5, 2, 6], 100))


if __name__ == '__main__':
    main()
