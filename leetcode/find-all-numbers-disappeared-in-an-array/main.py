#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://leetcode.cn/problems/find-all-numbers-disappeared-in-an-array/

from typing import List


class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
        visited = [False] * len(nums)

        for num in nums:
            visited[num - 1] = True

        res = []
        for i in range(len(nums)):
            if not visited[i]:
                res.append(i + 1)
        return res


def test_findDisappearedNumbers():
    s = Solution()

    # Test case 1
    nums1 = [4, 3, 2, 7, 8, 2, 3, 1]
    expected1 = [5, 6]
    assert s.findDisappearedNumbers(nums1) == expected1

    # Test case 2
    nums2 = [1, 1]
    expected2 = [2]
    assert s.findDisappearedNumbers(nums2) == expected2

    # Test case 3
    nums3 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    expected3 = []
    assert s.findDisappearedNumbers(nums3) == expected3

    # Test case 4
    nums4 = [10, 2, 5, 10, 9, 1, 1, 4, 3, 7]
    expected4 = [6, 8]
    assert s.findDisappearedNumbers(nums4) == expected4

    # Test case 5
    nums5 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    expected5 = [2, 3, 4, 5, 6, 7, 8, 9, 10]
    assert s.findDisappearedNumbers(nums5) == expected5

    print("All test cases pass")


def main():
    test_findDisappearedNumbers()


if __name__ == "__main__":
    main()
