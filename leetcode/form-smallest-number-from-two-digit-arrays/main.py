#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/form-smallest-number-from-two-digit-arrays/


# 给你两个只包含 1 到 9 之间数字的数组 nums1 和 nums2 ，每个数组中的元素 互不相同 ，请你返回 最小 的数字，两个数组都 至少 包含这个数字的某个数位。


# 示例 1：

# 输入：nums1 = [4,1,3], nums2 = [5,7]
# 输出：15
# 解释：数字 15 的数位 1 在 nums1 中出现，数位 5 在 nums2 中出现。15 是我们能得到的最小数字。
# 示例 2：

# 输入：nums1 = [3,5,2,6], nums2 = [3,1,7]
# 输出：3
# 解释：数字 3 的数位 3 在两个数组中都出现了。


from typing import List


class Solution:
    def minNumber(self, nums1: List[int], nums2: List[int]) -> int:
        s1, s2 = set(nums1), set(nums2)
        su = s1 & s2

        if su:
            return min(su)
        else:
            m1, m2 = min(nums1), min(nums2)
            m1, m2 = min(m1, m2), max(m1, m2)
            return int(str(m1) + str(m2))


def main():
    pass


if __name__ == "__main__":
    main()
